#include "myfind.h"

#define NB_OPTIONS 4

int fe_option_init(void)
{
    const char *available_options[NB_OPTIONS] =
    {
        "-d", "-H", "-L", "-P"
    };

    size_t i = 0;
    for (; i < NB_OPTIONS; i++)
    {
        if (!tok_util_add_option(available_options[i]))
            break;
    }

    return i == NB_OPTIONS;
}

void fe_option_set(struct file_explorer *fe, const char *option)
{
    switch (option[1])
    {
        case 'd':
            fe->options |= OPTION_PRE_ORDER;
            break;

        case 'H':
            fe->options |= OPTION_FOLLOW_SYM_CMD;
            break;

        case 'L':
            fe->options |= OPTION_FOLLOW_SYM;
            break;

        case 'P':
            fe->options &= ~OPTION_FOLLOW_SYM;
            break;
    }
}

void fe_option_parse(struct file_explorer *fe)
{
    const struct token *curr;
    while ((curr = tok_peek()) && curr->type == OPTION)
    {
        curr = tok_next();
        fe_option_set(fe, curr->symbol);
    }
}