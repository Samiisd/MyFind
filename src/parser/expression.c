#include "parser.h"
#include <err.h>

#define ERR_INVALID_TOKEN "cannot do '%s': invalid expression"

int expression(int mbp)
{
    const struct token *curr = tok_next();
    if (!curr || curr->type != EXPRESSION)
        errx(1, ERR_INVALID_TOKEN, tok_at_str(tok_cur_index() - 1));

    int left_ctx = curr->nud();

    curr = tok_peek();
    if (curr->type != EXPRESSION)
        errx(1, ERR_INVALID_TOKEN, tok_at_str(tok_cur_index() - 1));

    while (curr && curr->bp > mbp)
    {
        curr = tok_next();
        left_ctx = curr->led(left_ctx);
        curr = tok_peek();

        if (curr->type != EXPRESSION)
            errx(1, ERR_INVALID_TOKEN, tok_at_str(tok_cur_index() - 1));
    }

    return left_ctx;
}