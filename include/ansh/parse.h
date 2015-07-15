#ifndef ANSH_PARSE_H
#define ANSH_PARSE_H

#include "mpc.h"

mpc_parser_t *parser_word, *parser_number, *parser_builtin, *parser_variable,
             *parser_expression, *parser_command;

mpc_err_t *setup_parser();
void free_parser();

#endif
