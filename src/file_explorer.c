#include <stdlib.h>

#include "myfind.h"
#include "errors.h"

#include <unistd.h>
#include <stdio.h> /* WARNING : useless here */
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

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

static int run_ast_filter(struct file_explorer *fe, const char *pathname,
                          const struct ast_node *ast)
{
    if (!ast)
        return 1;

    switch (ast->type)
    {
        case TOKEN_ACTION_PRINT:
            printf("%s\n", pathname);
            return 1;
    }

    return !fe; /* WARNING : debug trick, must return 0 here */
}

int fe_find(struct file_explorer *fe, const char *dirpath)
{
    int res = 1;
    
    DIR *curr_dir = opendir(dirpath);

    if (!curr_dir)
    {
        warn(ERR_DEFAULT, "opening directory");
        return 0;
    }

    errno = 0;
    struct dirent *entry;
    while ((entry = readdir(curr_dir)))
    {
        run_ast_filter(fe, entry->d_name, fe->ast);
    }

    if (errno && !entry)
    {
        warn(ERR_DEFAULT, "parsing directory");
        res = 0;
    }

    closedir(curr_dir);
    return res;
}