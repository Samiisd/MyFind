#ifndef EXPR_PARSER_H
#define EXPR_PARSER_H

enum associativity
{
    left,
    right
}

struct operand
{
    const char *str;
    int bp; /* Binding Power */
    int asso; /* Associativity */
};

struct stream
{
    const char *expr[];
    size_t index;
};

struct operand_list
{
    const struct operand *list;
    size_t size;
};

int expr_parse(struct stream st, struct operand_list op_l);

#endif /* EXPR_PARSER_H */
