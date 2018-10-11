#include "tokenizer.h"

struct tok_stream
{
    char **arr;
    size_t size;
    size_t index;
};

static struct tok_stream stream =
{
    0
};

void tok_start(char **splitted_str, size_t nb_str)
{
    stream.arr = splitted_str;
    stream.size = nb_str;
    stream.index = 0;
}

const struct token *tok_peek(void)
{
    if (stream.index == stream.size)
        return NULL;

    return tok_find_token(stream.arr[stream.index + 1]);
}

const struct token *tok_next(void)
{
    if (stream.index == stream.size)
        return NULL;

    return tok_find_token(stream.arr[stream.index++]);
}