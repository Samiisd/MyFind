#include "hash_map.h"

#include <stdlib.h>
#include <stdio.h>

static size_t hash_function(const char *key, size_t table_size)
{
    size_t hash = 5381;

    for (size_t i = 0; key[i] != '\0'; i++)
        hash = ((hash << 5) + hash) + key[i];

    return hash % table_size;
}

struct hash_map *hash_init(size_t size, free_fnct free_val)
{
    struct hash_map *h = malloc(sizeof(struct hash_map));
    if (!h)
        return NULL;

    h->slots = calloc(size, sizeof(struct hash_slot*));
    if (!h->slots)
    {
        free(h);
        return NULL;
    }

    h->size = size;
    h->free_val = free_val;

    return h;
}

static void free_hash_slot(struct hash_slot *slot, free_fnct free_val)
{
    if (!slot)
        return;
    free_hash_slot(slot->next, free_val);

    free_val(slot->val);
    free(slot);
}

void hash_free(struct hash_map *map)
{
    if (!map || !map->slots)
        return;

    for(size_t i = 0; i < map->size; i++)
        free_hash_slot(map->slots[i], map->free_val);

    free(map->slots);
    free(map);
}

static struct hash_slot *make_hs(const char *name, void *val,
                                 struct hash_slot *next)
{
    struct hash_slot *hs = malloc(sizeof(struct hash_slot));
    if (!hs)
        return NULL;

    hs->name = name;
    hs->val = val;
    hs->next = next;

    return hs;
}

static int str_cmp(const char *s1, const char *s2)
{
    size_t i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] == s2[i];
}

static void *slot_find(struct hash_slot *hs, const char *value,
                       struct hash_slot **parent)
{
    if (!hs)
        return NULL;

    if (str_cmp(hs->name, value))
        return hs->val;

    if (parent)
        *parent = hs;

    return slot_find(hs->next, value, parent);
}

int hash_insert(struct hash_map *map, const char *name, void *val)
{
    if (!map || !map->slots || !name || !val)
        return 0;

    size_t index = hash_function(name, map->size);

    void *found_value = slot_find(map->slots[index], name, NULL);
    if (found_value)
        return 1;

    struct hash_slot *new_slot = make_hs(name, val, map->slots[index]);

    if (!new_slot)
        return 0;

    map->slots[index] = new_slot;

    return 1;
}

void *hash_find(const struct hash_map *map, const char *name)
{
    if (!map || !map->slots || !name)
        return NULL;

    size_t index = hash_function(name, map->size);
    return slot_find(map->slots[index], name, NULL);
}