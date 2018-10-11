#ifndef MYFIND_H
#define MYFIND_H

#include <stdint.h>

#include "tokenizer/tokenizer.h"

struct file_explorer
{
    int8_t options;
};

/* Options Handling */
#define OPTION_FOLLOW_SYM (1)
#define OPTION_FOLLOW_SYM_CMD (1 << 1)
#define OPTION_PRE_ORDER (1 << 2)

int fe_option_init(void);
void fe_option_set(struct file_explorer *fe, const char *option);
void fe_option_parse(struct file_explorer *fe);

static inline int fe_option_follow_sym(struct file_explorer *fe)
{
    return (fe->options & OPTION_FOLLOW_SYM) != 0;
}

static inline int fe_option_follow_sym_cmd(struct file_explorer *fe)
{
    return (fe->options & OPTION_FOLLOW_SYM_CMD) != 0;
}

static inline int fe_option_pre_order(struct file_explorer *fe)
{
    return (fe->options & OPTION_PRE_ORDER) != 0;
}


#endif /* MYFIND_H */