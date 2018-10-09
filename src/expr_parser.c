#include "expr_parser.h"

static const char *peek(struct stream *st)
{
    return st->expr[st->index];
}

static const char *next(struct stream *st)
{
    return st->expr[st->index++];
}

static int expr_parse_rec(struct stream *st, struct operand_list op_l, int mbp)
{

}

int expr_parse(struct stream *st, struct operand_list op_l)
{

}
