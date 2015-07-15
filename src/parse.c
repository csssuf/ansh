#include "ansh/parse.h"
#include "mpc.h"

mpc_err_t *setup_parser() {
    parser_word = mpc_new("word");
    parser_number = mpc_new("number");
    parser_builtin = mpc_new("builtin");
    parser_variable = mpc_new("variable");
    parser_expression = mpc_new("expression");
    parser_command = mpc_new("command");

    return mpca_lang(MPCA_LANG_DEFAULT,
        " word          : /[a-zA-Z0-9_\\-]+/ ;                                      "
        " number        : /[0-9]+/ ;                                                "
        " builtin       : (\"set\" | \"echo\") ;                                    "
        " variable      : '{' <word> '}';                                           "
        " expression    : (<builtin> | <word>) (<variable> | <number> | <word> )* ;  "
        " command       : /^/ <expression> /$/ ;                                    ",
        parser_word, parser_number, parser_builtin, parser_variable,
        parser_expression, parser_command, NULL);
}

void free_parser() {
    mpc_cleanup(6, parser_word, parser_number, parser_builtin, parser_variable,
                parser_expression, parser_command);
}
