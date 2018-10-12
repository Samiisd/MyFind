#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>
#include <stdlib.h>

#define TOK_MAP_SIZE 50

typedef void *(*nud_fnct)(void);
typedef void *(*led_fnct)(void *left_ctx);

enum type
{
    UNKNOWN,
    OPTION,
    EXPRESSION
};

struct token
{
    char *symbol;
    enum type type;

    int bp; /* Binding power of the token */

    nud_fnct nud;
    led_fnct led;
};

void tok_init(void);
int tok_add_token(struct token *tok);
struct token *tok_find_token(const char *tok_symbol);
void tok_free(void);

void tok_start(char **splitted_str, size_t nb_str);
void tok_stop();

const struct token *tok_peek(void);
const struct token *tok_next(void);
char *tok_next_str(void);
char *tok_at_str(size_t index);
size_t tok_cur_index(void);

int tok_util_add_option(char *symbole);
int tok_util_add_expression(char *symbole, int bp, nud_fnct nud,
                            led_fnct led);

#endif /* TOKENIZER_H */