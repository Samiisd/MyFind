#include "tokenizer/tokenizer.h"

int tok_util_add_option(char *symbol)
{
    struct token *new_token = calloc(1, sizeof(struct token));
    if (!new_token)
        return 0;

    new_token->type = OPTION;
    new_token->symbol = symbol;

    return tok_add_token(new_token);
}

int tok_util_add_expression(char *symbol, int bp, nud_fnct nud,
                            led_fnct led)
{
    struct token *new_token = calloc(1, sizeof(struct token));
    if (!new_token)
        return 0;

    new_token->type = EXPRESSION;
    new_token->symbol = symbol;
    new_token->bp = bp;
    new_token->nud = nud;
    new_token->led = led;

    return tok_add_token(new_token);
}