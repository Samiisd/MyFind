#ifndef CMDLINE_H
#define CMDLINE_H

/*
 * This header contains declaration of all the function in charge of parsing
 * command line arguments.
 */

#include "myfind.h"
#include "vector/vector.h"

/* Options Handling */
int cmd_option_init(void);
void cmd_option_parse(struct file_explorer *fe);

/* Files Handling */
struct vector *cmd_file_parse(void);


#endif /* CMDLINE_H */