#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>
#include <stdlib.h>

#define TOK_MAP_SIZE 50

struct token
{
    const char *symbol;

    int bp; /* Binding power of the token */

    int (*nud)(void);
    int (*led)(int left_ctx);
};

static inline
struct token *tok_build_token(const char *symbol, int bp,
                              int (*nud)(void), int (*led)(int left_ctx))
{
    struct token *res = malloc(sizeof(struct token));
    if (!res)
        return NULL;

    res->symbol = symbol;
    res->bp = bp;
    res->nud = nud;
    res->led = led;

    return res;
}

void tok_init(void);
int tok_add_token(struct token *tok);
struct token *tok_find_token(const char *tok_symbol);
void tok_free(void);

void tok_start(char **splitted_str, size_t nb_str, const struct token *tok_def);

const struct token *tok_peek(void);
const struct token *tok_next(void);
const char *tok_next_str(void);
const char *tok_at_str(size_t index);
size_t tok_cur_index(void);


#endif /* TOKENIZER_H */