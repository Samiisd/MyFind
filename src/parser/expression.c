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
    int left_ctx = tok_next()->nud();

    const struct token *curr = tok_peek();
    while (curr && curr->bp > mbp)
    {
        curr = tok_next();
        left_ctx = curr->led(left_ctx);
        curr = tok_peek();
    }

    return left_ctx;
}