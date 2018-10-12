#include "myfind.h"

void option_set(struct file_explorer *fe, const char *option)
{
    switch (option[1])
    {
        case 'd':
            fe->options |= OPTION_PRE_ORDER;
            break;

        case 'H':
            fe->options &= ~OPTION_FOLLOW_SYM;
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

int option_follow_sym(struct file_explorer *fe)
{
    return (fe->options & OPTION_FOLLOW_SYM) != 0;
}

int option_follow_sym_cmd(struct file_explorer *fe)
{
    return (fe->options & OPTION_FOLLOW_SYM_CMD) != 0;
}

int option_pre_order(struct file_explorer *fe)
{
    return (fe->options & OPTION_PRE_ORDER) != 0;
}