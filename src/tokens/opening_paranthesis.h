#ifndef OPENING_PARANTHESIS_H
#define OPENING_PARANTHESIS_H

#include <stdlib.h>
#include <err.h>
#include "parser/parser.h"

#define BP_OP 50
#define SYMBOL_OP "("

int nud_op()
{
    int res = expression(0);
    const char *curr_str = tok_next_str();
    if (!curr_str || curr_str[0] != ')')
        errx(1, "'(' expect ')' !");
    return res;
}

int led_op(int left_ctx)
{
    errx(1, "'(' should not be called as a function");
    return left_ctx;
}

struct token *token_op(void)
{
    return tok_build_token(SYMBOL_OP, BP_OP, nud_op, led_op);
}

#endif /* OPENING_PARANTHESIS_H */