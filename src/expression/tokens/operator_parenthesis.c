#include "expression/parser.h"
#include "expression/ast.h"
#include "expression/tokens/tokens.h"

#include "errors.h"

struct ast_node *led_operator_parenthesis_o(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, nud_operator_parenthesis_o());
}

struct ast_node *nud_operator_parenthesis_o(void)
{
    struct ast_node *res = expression_parse(BP_MIN);

    if (!res)
        errx(1, ERR_BAD_TOKEN_USE, "handling opening paranthesis", "(");

    const char *next = tok_next_str();
    if (!next || next[0] != ')')
        errx(1, ERR_BAD_TOKEN_USE, "finding closing paranthesis", "(");
    
    return res;
}

struct ast_node *led_operator_parenthesis_c(struct ast_node *left_ctx)
{
    errx(1, ERR_BAD_TOKEN_USE, "call to )", ")");
    return left_ctx;
}

struct ast_node *nud_operator_parenthesis_c(void)
{
    errx(1, ERR_BAD_TOKEN_USE, "call to )", ")");
    return NULL;
}
