#ifndef NODE_H
#define NODE_H

struct node
{
    void *data;

    struct node *left;
    struct node *right;
};

#endif /* NODE_H */