#ifndef VECTOR_H
#define VECTOR_H

struct vector
{
    void **data;
    size_t index;
    size_t capacity;

    void (*free_fnct)(void*);
};

struct vector *vector_init(size_t capacity, void (*free_fnct)(void*));
void vector_free(struct vector *v);

int vector_push(struct vector *v, void *item);
void vector_reset(struct vector *v);

void *vector_at(const struct vector *v, size_t index);
size_t vector_size(const struct vector *v);

#endif /* VECTOR_H */