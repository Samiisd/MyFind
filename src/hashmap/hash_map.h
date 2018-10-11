#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stddef.h>

struct hash_slot
{
    const char *name;
    void *val;
    struct hash_slot *next;
};

struct hash_map
{
    struct hash_slot **slots;
    size_t size;
};

struct hash_map *hash_init(size_t size);
void hash_free(struct hash_map *map);
int hash_insert(struct hash_map *map, const char *name, void *val);
void *hash_find(const struct hash_map *map, const char *name);

#endif /* !HASH_MAP_H */
