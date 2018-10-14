#ifndef TOKENS_H
#define TOKENS_H

#include <sys/stat.h>

#include "expression/ast.h"
#include "string/string.h"

#define TOKEN_THRESHOLD_OTHERS 0
#define TOKEN_THRESHOLD_OPERATORS (1 << 2)
#define TOKEN_THRESHOLD_TESTS (1 << 5)
#define TOKEN_THRESHOLD_ACTIONS (1 << 10)

#define BP_MAX 10
#define BP_MIN 0

#define BP_OP_OR 1
#define BP_OP_AND 2
#define BP_OP_NOT 3

enum tokens
{
    /* OTHERS */
    TOKEN_STRING = TOKEN_THRESHOLD_OTHERS,
    /* OPERATORS */
    TOKEN_OPERATOR_AND = TOKEN_THRESHOLD_OPERATORS,
    TOKEN_OPERATOR_OR,
    TOKEN_OPERATOR_NOT,
    /* TESTS*/
    TOKEN_TEST_NAME = TOKEN_THRESHOLD_TESTS,
    TOKEN_TEST_TYPE,
    /* ACTIONS */
    TOKEN_ACTION_PRINT = TOKEN_THRESHOLD_ACTIONS,
    TOKEN_ACTION_EXEC,
    TOKEN_ACTION_EXECDIR
};

static inline int token_is_action(int type)
{
    return type >= TOKEN_THRESHOLD_ACTIONS;
}

/* Operators */
struct ast_node *led_operator_and(struct ast_node *left_ctx);
struct ast_node *nud_operator_and(void);

struct ast_node *led_operator_or(struct ast_node *left_ctx);
struct ast_node *nud_operator_or(void);

struct ast_node *led_operator_not(struct ast_node *left_ctx);
struct ast_node *nud_operator_not(void);

/* Tests */
struct ast_node *led_test_name(struct ast_node *left_ctx);
struct ast_node *nud_test_name(void);
int handle_test_name(const struct ast_node *ast, const struct string *path);

struct ast_node *led_test_type(struct ast_node *left_ctx);
struct ast_node *nud_test_type(void);
int test_handle_type(const struct ast_node *ast, struct stat *st);

/* Actions */
struct ast_node *nud_action_print(void);
struct ast_node *led_action_print(struct ast_node *left_ctx);

struct ast_node *nud_action_exec(void);
struct ast_node *led_action_exec(struct ast_node *left_ctx);
int handle_action_exec(const struct ast_node *ast, const struct string *path);

struct ast_node *nud_action_execdir(void);
struct ast_node *led_action_execdir(struct ast_node *left_ctx);
int handle_action_execdir(const struct ast_node *ast, struct string *path);
#endif /* TOKENS_H */