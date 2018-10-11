#include "tokenizer.h"

struct tok_stream
{
    char **arr;
    size_t size;
    size_t index;

    const struct token *tok_def;
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

static const struct token *tok_get(size_t index)
{
    const struct token *found = tok_find_token(stream.arr[index]);

    if (!found)
        return stream.tok_def;

    return found;
}

const struct token *tok_peek(void)
{
    if (stream.index >= stream.size)
        return NULL;

    return tok_get(stream.index);
}

const struct token *tok_next(void)
{
    if (stream.index >= stream.size)
        return NULL;

    return tok_get(stream.index++);
}

const char *tok_next_str(void)
{
    if (stream.index >= stream.size)
        return NULL;

    return stream.arr[stream.index++];
}

const char *tok_at_str(size_t index)
{
    if (index >= stream.size)
        return NULL;

    return stream.arr[index];
}

size_t tok_cur_index(void)
{
    return stream.index;
}