#ifndef STRING_H
#define STRING_H

#include <stddef.h>

struct string
{
    char *buffer;
    int index;
    int capacity;
};

struct string *string_make(int capacity);
int string_append(struct string *str, const char *cstr);
void string_resize(struct string *str, int new_size);
int string_size(struct string *str);
void string_free(struct string *str);

int string_search_last(const struct string *str, char c);
#endif /* STRING_H */