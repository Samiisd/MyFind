#ifndef PARSER_H
#define PARSER_H

#include "tokenizer/tokenizer.h"

void *expression_parse(int mbp);

struct node *expression_build_ast(void);
#endif /* PARSER_H */