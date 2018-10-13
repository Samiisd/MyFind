#include "string.h"

#include <stdlib.h>

struct string *string_make(size_t capacity)
{
    struct string *str = malloc(sizeof(struct string));
    if (!str)
        return NULL;

    str->buffer = calloc(capacity, sizeof(char));
    if (!str->buffer)
    {
        free(str);
        return NULL;
    }

    str->capacity = capacity;
    str->index = 0;

    return str;
}

static int string_putchar(struct string *str, const char c)
{
    if (str->index >= str->capacity)
    {
        char *new_buffer = realloc(str->buffer, str->capacity * 2);
        if (!new_buffer)
            return 0;
        str->buffer = new_buffer;
        str->capacity *= 2;
    }

    str->buffer[str->index++] = c;
    return 1;
}

int string_append(struct string *str, const char *cstr)
{
    while (*cstr && string_putchar(str, *(cstr++)))
        continue;
    return *cstr == '\0';
}

size_t string_size(struct string *str)
{
    return str->index;
}

void string_resize(struct string *str, size_t new_size)
{
    str->index = new_size;
}

void string_free(struct string *str)
{
    free(str->buffer);
    free(str);
}