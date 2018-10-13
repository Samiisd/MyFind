#ifndef TEST_NAME_H
#define TEST_NAME_H

#include <stddef.h>

#include "expression/parser.h"
#include "expression/ast.h"
#include "expression/tokens/tokens.h"

#include "errors.h"

#define BP_TEST_NAME 1

struct ast_node *nud_test_name(void)
{
    const char *name_to_match = tok_next_str();
    if (!name_to_match)
        errx(1, ERR_BAD_TOKEN_USE, "handling right unary test", "-name");

    struct ast_node *res = ast_make(TOKEN_TEST_NAME, NULL, NULL);

    res->data = tok_get_buffer() + tok_get_index() - 1;
    res->nb_data = 1;

    return res;
}

struct ast_node *led_test_name(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, nud_test_name());
}

#endif /* TEST_NAME_H */