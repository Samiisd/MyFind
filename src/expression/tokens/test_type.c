#include "expression/parser.h"
#include "expression/tokens/tokens.h"
#include "errors.h"

#include <stddef.h>

struct ast_node *nud_test_type(void)
{
    const char *type_to_match = tok_next_str();
    if (!type_to_match)
        errx(1, ERR_BAD_TOKEN_USE, "handling right unary test", "-type");

    char available_type[7] =
    {
        'b', 'c', 'd', 'f', 'l', 'p', 's'
    };

    int i = 0;
    if (type_to_match[1] != '\0')
        i = 7;
    while (i < 7 && type_to_match[0] != available_type[i])
        i++;
    if (i == 7)
        errx(1, ERR_DEFAULT " : unknown type '%s'", "handling type",
             type_to_match);

    struct ast_node *res = ast_make(TOKEN_TEST_TYPE, NULL, NULL);

    res->data = tok_get_buffer() + tok_get_index() - 1;
    res->nb_data = 1;

    return res;
}

struct ast_node *led_test_type(struct ast_node *left_ctx)
{
    return ast_make(TOKEN_OPERATOR_AND, left_ctx, nud_test_type());
}

int test_handle_type(const struct ast_node *ast, struct stat *st)
{
    switch (ast->data[0][0])
    {
        case 'b':
            return S_ISBLK(st->st_mode);
        case 'c':
            return S_ISCHR(st->st_mode);
        case 'd':
            return S_ISDIR(st->st_mode);
        case 'f':
            return S_ISREG(st->st_mode);
        case 'l':
            return S_ISLNK(st->st_mode);
        case 'p':
            return S_ISFIFO(st->st_mode);
        case 's':
            return S_ISSOCK(st->st_mode);
    }

    return 0;
}