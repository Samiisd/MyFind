#include "tokenizer.h"

#include "hashmap/hash_map.h"

#include <stdlib.h>

static struct hash_map *map = NULL;

void tok_init(void)
{
    map = hash_init(TOK_MAP_SIZE, free);
}

int tok_add_token(struct token *tok)
{
    return hash_insert(map, tok->symbol, tok);
}

struct token *tok_find_token(const char *tok_symbol)
{
    return hash_find(map, tok_symbol);
}

void tok_free(void)
{
    hash_free(map);
    map = NULL;
}