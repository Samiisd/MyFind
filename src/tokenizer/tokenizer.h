#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

#define TOK_MAP_SIZE 50

struct token
{
    const char *symbol;

    int bp; /* Binding power of the token */

    int (*nud)(void);
    int (*led)(int left_ctx);
};

void tok_init(void);
int tok_add_token(struct token *tok);
struct token *tok_find_token(const char *tok_symbol);
void tok_free(void);

void tok_start(char **splitted_str, size_t nb_str, const struct token *tok_def);
const struct token *tok_peek(void);
const struct token *tok_next(void);
const char *tok_next_str(void);
const char *tok_peek_str(void);

#endif /* TOKENIZER_H */