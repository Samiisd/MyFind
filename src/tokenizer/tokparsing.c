#include "tokenizer.h"

#include "errors.h"

struct tok_stream
{
    char **arr;
    size_t size;
    size_t index;

    struct token *tok_unknown;
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

    stream.tok_unknown = calloc(1, sizeof(struct token *));
    if (!stream.tok_unknown)
        errx(1, ERR_NO_MEMORY_AVAILABLE, "init tokenizer engine");
}

static const struct token *tok_get(size_t index)
{
    const struct token *found = tok_find_token(stream.arr[index]);

    if (!found)
    {
        stream.tok_unknown->symbol = stream.arr[index];
        stream.tok_unknown->type = UNKNOWN;

        return stream.tok_unknown;
    }

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

char *tok_next_str(void)
{
    if (stream.index >= stream.size)
        return NULL;

    return stream.arr[stream.index++];
}

char *tok_at_str(size_t index)
{
    if (index >= stream.size)
        return NULL;

    return stream.arr[index];
}

size_t tok_cur_index(void)
{
    return stream.index;
}