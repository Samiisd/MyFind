#include "expression/tokens/tokens.h"
#include "tokenizer/tokenizer.h"
#include "errors.h"

#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

struct ast_node *nud_action_execdir(void)
{       
    const char *end;
    int nb_arg = 0;
    while ((end = tok_next_str()) &&  end[0] != ';')
        nb_arg++;
    if (!nb_arg)
        errx(1, ERR_BAD_TOKEN_USE, "finding argument", "-execdir");
    if (!end)
        errx(1, ERR_BAD_TOKEN_USE, "finding ending semi-colon", "-execdir");

    struct ast_node *res = ast_make(TOKEN_ACTION_EXECDIR, NULL, NULL);

    res->data = tok_get_buffer() + tok_get_index() - 1 - nb_arg;
    res->nb_data = nb_arg;

    return res;
}

struct ast_node *led_action_execdir(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, nud_action_execdir());
}

int handle_action_execdir(const struct ast_node *ast,
                          struct string *path)
{
    int last_slash = string_search_last(path, '/');

    struct string *new_name = string_make_ptr(string_size(path) + 3);
    string_append(new_name, "./");
    string_append(new_name, path->buffer + last_slash + 1);

    char *args[ast->nb_data + 1];
    for (int i = 0; i < ast->nb_data; i++)
        args[i] = expend_arg(new_name, ast->data[i]).buffer;

    args[ast->nb_data] = NULL;

    int id = fork();
    if (id == -1)
    {
        warn(ERR_DEFAULT, "fork");
        return 0;
    }

    if (id == 0) /* In Child */
    {
        if (last_slash > -1)
            string_resize(path, last_slash);

        if (chdir(path->buffer) != 0)
            err(1, ERR_DEFAULT, "changing directory");

        execvp(args[0], args);
        err(1, ERR_DEFAULT, "exec file");
    }

    string_free(new_name);

    int child_ret_val = 1;
    if (waitpid(id, &child_ret_val, 0) == id)
        child_ret_val = WEXITSTATUS(child_ret_val); 

    for (int i = 0; i < ast->nb_data; i++)
        free(args[i]);

    return child_ret_val == 0;
}