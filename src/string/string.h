#ifndef STRING_H
#define STRING_H

#include <stddef.h>

struct string
{
    char *buffer;
    size_t index;
    size_t capacity;
};

struct string *string_make(size_t capacity);
int string_append(struct string *str, const char *cstr);
void string_resize(struct string *str, size_t new_size);
size_t string_size(struct string *str);
void string_free(struct string *str);

#endif /* STRING_H */