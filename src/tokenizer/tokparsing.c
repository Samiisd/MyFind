#include "tokenizer.h"

#include "errors.h"

extern struct tok_stream stream;

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