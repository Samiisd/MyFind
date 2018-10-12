#ifndef TREE_H
#define TREE_H

struct tree_node
{
    void *data;

    struct tree_node *left;
    struct tree_node *right;
};

void tree_free(struct tree_node *root, void (*free_fct)(void*));

#endif /* TREE_H */