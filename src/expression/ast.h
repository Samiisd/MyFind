#ifndef AST_H
#define AST_H

#include "expression/tokens/tokens.h"

struct ast_node
{
    int type;
    const char **data;
    int nb_data;

    struct ast_node *left;
    struct ast_node *right;
};

struct ast_node *ast_make(int type, struct ast_node *left,
                          struct ast_node *right);
void ast_free(struct ast_node *root, void (*free_fct)(void*));

#endif /* AST_H */