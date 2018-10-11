#ifndef TIMES_H
#define TIMES_H

#include <stdlib.h>
#include "parser/parser.h"

#define BP_TIMES 2
#define SYMBOL_TIMES "*"

int nud_times()
{
    return atoi(tok_next_str());
}

int led_times(int left_ctx)
{
    return left_ctx * expression(BP_TIMES);
}

struct token *token_times(void)
{
    return tok_build_token(SYMBOL_TIMES, BP_TIMES, nud_times, led_times);
}

#endif /* TIMES_H */