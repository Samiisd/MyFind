#ifndef ACTION_PRINT_H
#define ACTION_PRINT_H

#include <stddef.h>

#include "expression/ast.h"
#include "expression/tokens/tokens.h"

#include "errors.h"

struct ast_node *led_action_print(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_ACTION_PRINT, left_ctx, NULL);
}

struct ast_node *nud_action_print(void)
{
    return led_action_print(NULL);
}

#endif /* ACTION_PRINT_H */