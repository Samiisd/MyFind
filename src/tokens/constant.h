#ifndef CONSTANT_H
#define CONSTANT_H

#include <err.h>
#include <stdlib.h>
#include "parser/parser.h"

#define BP_CONSTANT 1

int nud_constant()
{
    return atoi(tok_at_str(tok_cur_index() - 1));
}

int led_constant(int left_ctx)
{
    errx(1, "constants cannot take arguments");
    return left_ctx;
}

struct token *token_constant(void)
{
    return tok_build_token(NULL, BP_CONSTANT, nud_constant, led_constant);
}

#endif /* CONSTANT_H */