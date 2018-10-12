#include <stdlib.h>

#include "myfind.h"
#include "errors.h"

struct file_explorer *fe_init()
{
    struct file_explorer *fe = calloc(1, sizeof(struct file_explorer));
    if (!fe)
        errx(1, ERR_NO_MEMORY_AVAILABLE, "initialize file explorer");

    return fe;
}

void fe_free(struct file_explorer *fe)
{
    tree_free(fe->ast, NULL);
    free(fe);
}