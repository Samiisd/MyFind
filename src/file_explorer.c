#define _XOPEN_SOURCE 700
//#define _GNU_SOURCE

#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>

#include "myfind.h"
#include "errors.h"
#include "string/string.h"

struct file_explorer *fe_init()
{
    struct file_explorer *fe = calloc(1, sizeof(struct file_explorer));
    if (!fe)
        errx(1, ERR_NO_MEMORY_AVAILABLE, "initialize file explorer");

    return fe;
}

void fe_free(struct file_explorer *fe)
{
    ast_free(fe->ast, NULL);
    free(fe);
}

static int run_ast_filter(struct file_explorer *fe, struct string *path,
                          const struct ast_node *ast, struct stat *st)
{
    if (!ast)
        return 1;

    switch (ast->type)
    {
        case TOKEN_ACTION_PRINT:
            printf("%s\n", path->buffer);
            return 1;
        case TOKEN_ACTION_EXEC:
            return handle_action_exec(ast, path);
        case TOKEN_ACTION_EXECDIR:
            return handle_action_execdir(ast, path);
        case TOKEN_TEST_NAME:
            return handle_test_name(ast, path);
        case TOKEN_TEST_TYPE:
            return test_handle_type(ast, st);
        case TOKEN_OPERATOR_AND:
            return run_ast_filter(fe, path, ast->left, st) &&
                   run_ast_filter(fe, path, ast->right, st);
        case TOKEN_OPERATOR_OR:
            return run_ast_filter(fe, path, ast->left, st) ||
                   run_ast_filter(fe, path, ast->right, st);
    }

    return 0;
}

static int str_cmp(const char *s1, const char *s2)
{
    size_t i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] == s2[i];
}

static int fe_handle_dirs(struct file_explorer *fe, struct string *dirpath,
                          struct stat *st);
static int fe_handle_file(struct file_explorer *fe, struct string *path,
                          int from_cmdline);
static int fe_handle_files(struct file_explorer *fe, struct string *dirpath,
                           DIR *curr_dir);

static int fe_handle_dirs(struct file_explorer *fe, struct string *dirpath,
                          struct stat *st)
{
    if (!option_pre_order(fe))
        run_ast_filter(fe, dirpath, fe->ast, st);

    int dirpath_len = string_size(dirpath);
    
    int res;

    int fd = open(dirpath->buffer, O_RDONLY | O_CLOEXEC);

    DIR *curr_dir = NULL;
    if (fd == -1 || !(curr_dir = fdopendir(fd)))
    {
        warn(ERR_DEFAULT, "opening directory");
        res = 0;
    }
    else
        res = fe_handle_files(fe, dirpath, curr_dir);

    if (option_pre_order(fe))
    {
        string_resize(dirpath, dirpath_len);
        run_ast_filter(fe, dirpath, fe->ast, st);
    }

    if (fd != -1)
        close(fd);
    if (curr_dir)
        closedir(curr_dir);

    return res;
}

static int fe_handle_file(struct file_explorer *fe, struct string *path,
                          int from_cmdline)
{
    struct stat st;
    int res;
    if (option_follow_sym(fe) || (from_cmdline && option_follow_sym_cmd(fe)))
        res = stat(path->buffer, &st) == 0;
    else
        res = lstat(path->buffer, &st) == 0;

    if (!res)
    {
        warn(ERR_DEFAULT, "file get info");
        return 0;
    }

    if (S_ISDIR(st.st_mode))
        return fe_handle_dirs(fe, path, &st) && res;

    return run_ast_filter(fe, path, fe->ast, &st) && res;
}

static int fe_handle_files(struct file_explorer *fe, struct string *dirpath,
                           DIR *curr_dir)
{
    if (dirpath->buffer[string_size(dirpath) - 1] != '/')
        string_append(dirpath, "/");
    int dirpath_len = string_size(dirpath);

    errno = 0;
    struct dirent *entry;

    int res = 1;
    while ((entry = readdir(curr_dir)))
    {
        if (str_cmp(entry->d_name, ".") || str_cmp(entry->d_name, ".."))
            continue;

        string_append(dirpath, entry->d_name);

        res = fe_handle_file(fe, dirpath, 0) && res;

        string_resize(dirpath, dirpath_len);
        errno = 0;
    }

    if (errno && !entry)
    {
        warn(ERR_DEFAULT, "parsing directory");
        return 0;
    }

    return res;
}

int fe_find(struct file_explorer *fe, const char *dirpath)
{
    struct string *path_root = string_make(PATH_MAX);
    if (!string_append(path_root, dirpath))
    {
        warnx(ERR_NO_MEMORY_AVAILABLE, "parsing directory");
        return 0;
    }

    int res = fe_handle_file(fe, path_root, 1);

    string_free(path_root);

    return res;
}