#include "tokenizer/tokenizer.h"
#include "vector/vector.h"
#include "errors.h"
#include "myfind.h"

#include <stdio.h> /* WARNING : useless here */
#include <stddef.h>
#include <err.h>

#define OPTION_NB 4
#define FILE_CAPACITY 10

/* Option parsing */
int cmd_option_init(void)
{
    char *available_options[OPTION_NB] =
    {
        "-d", "-H", "-L", "-P"
    };

    size_t i = 0;
    while (i < OPTION_NB && tok_util_add_option(available_options[i]))
        i++;

    return i == OPTION_NB;
}

void cmd_option_parse(struct file_explorer *fe)
{
    printf("parsing options : ");
    const struct token *curr;
    while ((curr = tok_peek()) && curr->type == OPTION)
    {
        curr = tok_next();
        printf("%s ", curr->symbol);
        option_set(fe, curr->symbol);
    }

    printf("\n");
}

/* Files parsing */
struct vector *cmd_file_parse(void)
{
    printf("parsing files : ");
    struct vector *v = vector_init(FILE_CAPACITY, NULL);
    if (!v)
        errx(1, ERR_NO_MEMORY_AVAILABLE, "file parsing");
    
    const struct token *curr;
    while ((curr = tok_peek()) && curr->type == UNKNOWN)
    {
        curr = tok_next();

        if (curr->symbol[0] == '-')
            errx(1, ERR_UNKNOWN_PREDICATE, "file parsing", curr->symbol);

        printf("%s ", curr->symbol);

        if (!vector_push(v, curr->symbol))
            errx(1, ERR_NO_MEMORY_AVAILABLE, "file parsing");
    }

    printf("\n");

    if (vector_size(v) == 0 && !vector_push(v, "."))
        errx(1, ERR_NO_MEMORY_AVAILABLE, "file parsing");

    return v;
}