#include "errors.h"
#include "expression/parser.h"

#include <err.h>

void *expression_parse(int mbp)
{
    const struct token *curr = tok_peek();
    if (!curr)
        return NULL;

    if (curr->type != EXPRESSION)
        errx(1, ERR_INVALID_TOKEN, tok_at_str(tok_cur_index() - 1));

    curr = tok_next();

    void *left_ctx = curr->nud();

    curr = tok_peek();
    if (curr && curr->type != EXPRESSION)
        errx(1, ERR_INVALID_TOKEN, tok_at_str(tok_cur_index() - 1));

    while (curr && curr->bp > mbp)
    {
        curr = tok_next();
        left_ctx = curr->led(left_ctx);
        curr = tok_peek();

        if (!curr)
            return left_ctx;
        if (curr->type != EXPRESSION)
            errx(1, ERR_INVALID_TOKEN, tok_at_str(tok_cur_index() - 1));
    }

    return left_ctx;
}