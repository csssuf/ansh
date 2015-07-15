#include "ansh/parse.h"
#include "mpc.h"

mpc_err_t *setup_parser() {
    word = mpc_new("word");
    number = mpc_new("number");
    builtin = mpc_new("builtin");
    variable = mpc_new("variable");
    expression = mpc_new("number");
    command = mpc_new("command");

    return mpca_lang(MPCA_LANG_DEFAULT,
        " word          : /[a-zA-Z0-9_\\-]*/ ;                                      "
        " number        : /[0-9]+/ ;                                                "
        " builtin       : \"set\" | \"echo\" ;                                      "
        " variable      : $<word> ;                                                 "
        " expression    : <word> | <builtin> ( <word> | <number> | <variable> )* ;  ");
}
