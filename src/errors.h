#ifndef ERRORS_H
#define ERRORS_H

#include <err.h>

#define ERR_DEFAULT "cannot do '%s'"

/* Global Errors */
#define ERR_NO_MEMORY_AVAILABLE ERR_DEFAULT " : no memory available"

/* Option Parser Errors */
#define ERR_UNKNOWN_PREDICATE ERR_DEFAULT " : unknown predicate '%s'"

/* Expression Parser Errors */
#define ERR_INVALID_TOKEN ERR_DEFAULT " : invalid expression"
#define ERR_BAD_TOKEN_USE ERR_DEFAULT " : bad use of '%s'"

#endif /* ERRORS_H */