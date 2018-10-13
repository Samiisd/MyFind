#include "expression/ast.h"

#include <stdlib.h>

struct ast_node *ast_make(int type, struct ast_node *left,
                          struct ast_node *right)
{
    struct ast_node *res = malloc(sizeof(struct ast_node));
    if (!res)
        return NULL;

    res->type = type;

    res->data = NULL;
    res->nb_data = 0;

    res->left = left;
    res->right = right;

    return res;
}

void ast_free(struct ast_node *root, void (*free_fct)(void*))
{
    if (!root)
        return;

    ast_free(root->left, free_fct);
    ast_free(root->right, free_fct);

    if (free_fct)
        free_fct(root->data);

    free(root);
}