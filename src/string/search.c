#include "string.h"

int string_search_last(const struct string *str, char c)
{
    int i = str->index - 1;
    while (i >= 0 && str->buffer[i] != c)
        i--;
    return i;
}