#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

struct vector *vector_init(size_t capacity, void (*free_fnct)(void*))
{
    struct vector *v = malloc(sizeof(struct vector));
    if (!v)
        return NULL;
    
    v->capacity = capacity;
    v->index = 0;
    v->free_fnct = free_fnct;
    v->data = malloc(sizeof(void *) * capacity);

    if (!v->data)
    {
        free(v);
        return NULL;
    }

    return v;
}

static int vector_resize(struct vector *v, int capacity)
{

    void **new_data = realloc(v->data, sizeof(void *) * capacity);
    if (!new_data)
        return 0;

    v->data = new_data;
    v->capacity = capacity;

    return 1;
}

int vector_push(struct vector *v, void *item)
{
    if (v->index == v->capacity && !vector_resize(v, v->capacity * 2))
        return 0;

    v->data[v->index++] = item;
    return 1;
}

void vector_reset(struct vector *v)
{
    v->index = 0;
}

void *vector_at(const struct vector *v, size_t index)
{
    if (index >= v->index)
        return NULL;

    return v->data[index];
}

size_t vector_size(const struct vector *v)
{
    return v->index;
}

void vector_free(struct vector *v)
{
    if (v->free_fnct)
    {
        for (size_t i = 0; i < vector_size(v); i++)
            v->free_fnct(v->data[i]);
    }

    free(v->data);
    free(v);
}