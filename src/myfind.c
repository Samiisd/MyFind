#include <stdio.h>

#include "myfind.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    /* Initialisation of engines */
    tok_init();
    fe_option_init();

    tok_start(argv + 1, argc - 1);

    tok_free();
    return 0;
}