#include "expression/tree.h"

#include <stdlib.h>

struct tree_node *tree_make(void *data, struct tree_node *left,
                            struct tree_node *right)
{
    struct tree_node *res = malloc(sizeof(struct tree_node));
    if (!res)
        return NULL;

    res->data = data;
    res->left = left;
    res->right = right;

    return res;
}

void tree_free(struct tree_node *root, void (*free_fct)(void*))
{
    if (!root)
        return;

    tree_free(root->left, free_fct);
    tree_free(root->right, free_fct);

    if (free_fct)
        free_fct(root->data);

    free(root);
}