#include "string.h"

int string_search_last(const struct string *str, char c)
{
    int i = str->index - 1;
    while (i >= 0 && str->buffer[i] != c)
        i--;
    return i;
}

int cstr_search_str(const char *str, const char *sub)
{
    for (int i = 0; str[i]; i++)
    {
        int j = 0;
        for (; str[i + j] && str[i + j] == sub[j]; j++)
            continue;
        if (!sub[j])
            return i;
    }
    return -1;
}