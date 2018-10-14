#include "expression/tokens/tokens.h"
#include "tokenizer/tokenizer.h"
#include "errors.h"

#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

struct ast_node *nud_action_exec(void)
{       
    const char *end;
    int nb_arg = 0;
    while ((end = tok_next_str()) &&  end[0] != ';')
        nb_arg++;
    if (!nb_arg)
        errx(1, ERR_BAD_TOKEN_USE, "finding argument", "-exec");
    if (!end)
        errx(1, ERR_BAD_TOKEN_USE, "finding ending semi-colon", "-exec");

    struct ast_node *res = ast_make(TOKEN_ACTION_EXEC, NULL, NULL);

    res->data = tok_get_buffer() + tok_get_index() - 1 - nb_arg;
    res->nb_data = nb_arg;

    return res;
}

struct ast_node *led_action_exec(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, nud_action_exec());
}

int handle_action_exec(const struct ast_node *ast, const struct string *path)
{
    char *args[ast->nb_data + 1];
    for (int i = 0; i < ast->nb_data; i++)
    {
        if (ast->data[i][0] == '{' && ast->data[i][1] == '}')
            args[i] = path->buffer;
        else
            args[i] = ast->data[i];
    }

    args[ast->nb_data] = NULL;

    int id = fork();
    if (id == -1)
    {
        warn(ERR_DEFAULT, "fork");
        return 0;
    }

    if (id == 0) /* In Child */
    {
        execvp(args[0], args);
        err(1, ERR_DEFAULT, "exec file");
    }

    return waitpid(id, NULL, 0);
}