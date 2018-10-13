#ifndef TOKENS_H
#define TOKENS_H

#define TOKEN_THRESHOLD_OTHERS 0
#define TOKEN_THRESHOLD_OPERATORS (1 << 2)
#define TOKEN_THRESHOLD_TESTS (1 << 5)
#define TOKEN_THRESHOLD_ACTIONS (1 << 10)

enum tokens
{
    /* OTHERS */
    TOKEN_STRING = TOKEN_THRESHOLD_OTHERS,
    /* OPERATORS */
    TOKEN_OPERATOR_AND = TOKEN_THRESHOLD_OPERATORS,
    /* TESTS*/
    /* ACTIONS */
    TOKEN_ACTION_PRINT = TOKEN_THRESHOLD_ACTIONS
};

static inline int token_is_action(int type)
{
    return type >= TOKEN_THRESHOLD_ACTIONS;
}

#endif /* TOKENS_H */