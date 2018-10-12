#ifndef MYFIND_H
#define MYFIND_H

#include <stdint.h>

#include "expression/tree.h"

struct file_explorer
{
    struct tree_node *ast;
    int8_t options;
};

/* File Explorer */
struct file_explorer *fe_init();
void fe_free(struct file_explorer *fe);

/* OPTIONS */
#define OPTION_FOLLOW_SYM (1)
#define OPTION_FOLLOW_SYM_CMD (1 << 1)
#define OPTION_PRE_ORDER (1 << 2)

void option_set(struct file_explorer *fe, const char *option);
int option_follow_sym(struct file_explorer *fe);
int option_follow_sym_cmd(struct file_explorer *fe);
int option_pre_order(struct file_explorer *fe);

#endif /* MYFIND_H */