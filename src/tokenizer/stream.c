#include "tokenizer.h"

#include "errors.h"

struct tok_stream stream =
{
    0
};

void tok_start(char **splitted_str, size_t nb_str)
{
    stream.arr = splitted_str;
    stream.size = nb_str;
    stream.index = 0;

    stream.tok_unknown = calloc(1, sizeof(struct token *));
    if (!stream.tok_unknown)
        errx(1, ERR_NO_MEMORY_AVAILABLE, "init tokenizer engine");
}

void tok_stop(void)
{
    stream.arr = NULL;
    stream.size = 0;
    stream.index = 0;

    free(stream.tok_unknown);
}

char **tok_get_buffer(void)
{
    return stream.arr;
}

size_t tok_get_index(void)
{
    return stream.index;
}

size_t tok_get_size(void)
{
    return stream.size;
}