#include "parser.h"

/*
Expression(int bp): 
    Left = next().nud() 
    Curr = peek() 
    While Curr && Curr.BP > bp: 
    Curr = next() 
    Left = curr.led(left) 
    Curr = peek() 

    Return left
*/

int expression(int mbp)
{
    const struct token *curr = tok_next();
    if (!curr || curr->type != EXPRESSION)
        errx(1, "'%s' is not a valid expression", 
             tok_at_str(tok_cur_index() - 1));

    int left_ctx = curr->nud();

    curr = tok_peek();
    if (curr->type != EXPRESSION)
        errx(1, "'%s' is not a valid expression",
             tok_at_str(tok_cur_index() - 1));

    while (curr && curr->bp > mbp)
    {
        curr = tok_next();
        left_ctx = curr->led(left_ctx);
        curr = tok_peek();

        if (curr->type != EXPRESSION)
            errx(1, "'%s' is not a valid expression",
                 tok_at_str(tok_cur_index() - 1));
    }

    return left_ctx;
}