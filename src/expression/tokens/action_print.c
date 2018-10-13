#include <stddef.h>

#include "expression/ast.h"
#include "expression/tokens/tokens.h"

#include "errors.h"

struct ast_node *nud_action_print(void)
{
    return ast_make(TOKEN_ACTION_PRINT, NULL, NULL);
}

struct ast_node *led_action_print(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, nud_action_print());
}