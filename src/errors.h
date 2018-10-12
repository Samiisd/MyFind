#ifndef ERRORS_H
#define ERRORS_H

#include <err.h>

/* Global Errors */
#define ERR_NO_MEMORY_AVAILABLE "cannot do '%s' : no memory available"

/* Option Parser Errors */
#define ERR_UNKNOWN_PREDICATE "cannot do '%s' : unknown predicate '%s'"

/* Expression Parser Errors */
#define ERR_INVALID_TOKEN "cannot do '%s': invalid expression"

#endif /* ERRORS_H */