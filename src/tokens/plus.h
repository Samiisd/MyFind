#ifndef PLUS_H
#define PLUS_H

#include <stdlib.h>
#include "parser/parser.h"

#define BP_PLUS 1
#define SYMBOL_PLUS "+"

int nud_plus()
{
    return atoi(tok_next_str());
}

int led_plus(int left_ctx)
{
    return left_ctx + expression(BP_PLUS);
}

struct token *token_plus(void)
{
    return tok_build_token(SYMBOL_PLUS, BP_PLUS, nud_plus, led_plus);
}

#endif /* PLUS_H */