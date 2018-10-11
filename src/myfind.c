#include <stdio.h>

#include "tokenizer/tokenizer.h"
#include "parser/parser.h"
#include "tokens/plus.h"
#include "tokens/times.h"
#include "tokens/constant.h"
#include "tokens/opening_paranthesis.h"
#include "tokens/closing_paranthesis.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    
    for (int i = 1; i < argc; i++)
        printf("%s ", argv[i]);

    tok_init();

    tok_add_token(token_plus());
    tok_add_token(token_times());
    tok_add_token(token_cp());
    tok_add_token(token_op());
    
    struct token *const_tok = token_constant();
    tok_start(argv + 1, argc - 1, const_tok);
    
    printf("= %d\n", expression(0));

    free(const_tok);
    tok_free();
    return 0;
}