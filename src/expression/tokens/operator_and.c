#include <stddef.h>

#include "expression/parser.h"
#include "expression/ast.h"
#include "expression/tokens/tokens.h"

#include "errors.h"

struct ast_node *led_operator_and(struct ast_node *left_ctx)
{
    struct ast_node *right = expression_parse(BP_OP_AND);
    if (!right)
        errx(1, ERR_BAD_TOKEN_USE, "handling binary operator", "-a");
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, right);
}

struct ast_node *nud_operator_and(void)
{
    errx(1, ERR_BAD_TOKEN_USE, "handling binary operator", "-a");
    return NULL;
}