#include <stddef.h>

#include "expression/parser.h"
#include "expression/ast.h"
#include "expression/tokens/tokens.h"

#include "errors.h"

struct ast_node *led_operator_not(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, nud_operator_not());
}

struct ast_node *nud_operator_not(void)
{
    struct ast_node *left = expression_parse(BP_OP_NOT);
    if (!left)
        errx(1, ERR_BAD_TOKEN_USE, "handling unary operator", "!");
    return ast_make(TOKEN_OPERATOR_NOT, left, NULL);
}