#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdlib.h>

struct string
{
    char *buffer;
    int index;
    int capacity;
};

struct string string_make(int capacity);
struct string *string_make_ptr(int capacity);
int string_append(struct string *str, const char *cstr);
int string_append_n(struct string *str, const char *cstr, int n);
void string_resize(struct string *str, int new_size);

int string_search_last(const struct string *str, char c);
int cstr_search_str(const char *str, const char *sub);

static inline void string_free(struct string *str)
{
    free(str->buffer);
    free(str);
}

static inline int string_size(struct string *str)
{
    return str->index;
}

#endif /* STRING_H */