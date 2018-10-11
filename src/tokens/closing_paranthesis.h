#ifndef CLOSING_PARANTHESIS_H
#define CLOSING_PARANTHESIS_H

#include <stdlib.h>
#include <err.h>
#include "parser/parser.h"

#define BP_CP 0
#define SYMBOL_CP ")"

int nud_cp()
{
    errx(1, "')' should not be called as an unary function");
    return 0;
}

int led_cp(int left_ctx)
{
    errx(1, "')' should not be called as binary function");
    return left_ctx;
}

struct token *token_cp(void)
{
    return tok_build_token(SYMBOL_CP, BP_CP, nud_cp, led_cp);
}

#endif /* CLOSING_PARANTHESIS_H */