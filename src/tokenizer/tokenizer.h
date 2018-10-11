#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>
#include <stdlib.h>

#define TOK_MAP_SIZE 50

typedef int (*nud_fnct)(void);
typedef int (*led_fnct)(int left_ctx);

enum type
{
    UNKNOWN,
    OPTION,
    EXPRESSION
};

struct token
{
    const char *symbol;
    enum type type;

    int bp; /* Binding power of the token */

    nud_fnct nud;
    led_fnct led;
};

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

int tok_util_add_option(const char *symbole);
int tok_util_add_expression(const char *symbole, int bp, nud_fnct nud,
                            led_fnct led);

#endif /* TOKENIZER_H */