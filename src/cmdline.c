#include "tokenizer/tokenizer.h"
#include "vector/vector.h"
#include "errors.h"
#include "myfind.h"

#include <stddef.h>
#include <err.h>

#define OPTION_NB 4
#define FILE_CAPACITY 10

/* Option parsing */
int cmd_option_init(void)
{
    char *available_options[OPTION_NB] =
    {
        "-d", "-H", "-L", "-P"
    };

    size_t i = 0;
    while (i < OPTION_NB && tok_util_add_option(available_options[i]))
        i++;

    return i == OPTION_NB;
}

void cmd_option_parse(struct file_explorer *fe)
{
    const struct token *curr;
    while ((curr = tok_peek()) && curr->type == OPTION)
    {
        curr = tok_next();
        option_set(fe, curr->symbol);
    }
}

/* Files parsing */
struct vector *cmd_file_parse(void)
{
    struct vector *v = vector_init(FILE_CAPACITY, NULL);
    if (!v)
        errx(1, ERR_NO_MEMORY_AVAILABLE, "file parsing");
    
    const struct token *curr;
    while ((curr = tok_peek()) && curr->type == UNKNOWN)
    {
        curr = tok_next();

        if (curr->symbol[0] == '-')
            errx(1, ERR_UNKNOWN_PREDICATE, "file parsing", curr->symbol);

        if (!vector_push(v, curr->symbol))
            errx(1, ERR_NO_MEMORY_AVAILABLE, "file parsing");
    }

    if (vector_size(v) == 0 && !vector_push(v, "."))
        errx(1, ERR_NO_MEMORY_AVAILABLE, "file parsing");

    return v;
}

/* Expression parsing */
#include "expression/parser.h"
#include "expression/tokens/action_print.h"
#include "expression/tokens/operator_and.h"
#include "expression/tokens/operator_or.h"

int cmd_expression_init(void)
{
    int res = tok_util_add_expression("-print", 1, nud_action_print,
                                      led_action_print) &&
              tok_util_add_expression("-a", BP_OP_AND, nud_operator_and,
                                      led_operator_and) &&
              tok_util_add_expression("-o", BP_OP_OR, nud_operator_or,
                                      led_operator_or);
    return res;
}

static int contains_action(struct ast_node *ast)
{
    if (!ast)
        return 0;

    return token_is_action(ast->type) || contains_action(ast->left) ||
           contains_action(ast->right);
}

struct ast_node *cmd_expression_parse(void)
{
    //const struct token *curr = tok_peek();
    //if (!curr || curr->type != EXPRESSION)
    //    return NULL;

    struct ast_node *ast = expression_parse(0);
    if (!ast || !contains_action(ast))
        ast = ast_make(TOKEN_OPERATOR_AND, ast, nud_action_print());

    return ast;
}