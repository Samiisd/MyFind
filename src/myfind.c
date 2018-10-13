#include <stdio.h>

#include "myfind.h"
#include "cmdline.h"
#include "tokenizer/tokenizer.h"

int main(int argc, char *argv[])
{
    /* Variable initialisation */
    struct file_explorer *fe = fe_init();

    /* Engines initialisation */
    tok_init();
    cmd_option_init();
    cmd_expression_init();

    tok_start(argv + 1, argc - 1);

    /* Argument parsing */
    cmd_option_parse(fe);
    struct vector *files = cmd_file_parse();
    fe->ast = cmd_expression_parse();

    int res = 0;
    for (size_t i = 0; i < vector_size(files); i++)
        res = !fe_find(fe, files->data[i]) || res;

    /* Resource release*/
    tok_stop();
    tok_free();
    vector_free(files);
    fe_free(fe);

    return res;
}