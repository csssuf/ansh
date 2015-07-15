#ifndef ANSH_PARSE_H
#define ANSH_PARSE_H

#include "mpc.h"

mpc_parser_t *word, *number, *builtin, *variable, *expression, *command;

mpc_err_t *setup_parser();

#endif
