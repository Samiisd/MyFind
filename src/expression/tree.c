#include "expression/tree.h"

#include <stdlib.h>

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