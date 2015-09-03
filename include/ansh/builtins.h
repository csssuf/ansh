#ifndef ANSH_BUILTINS_H
#define ANSH_BUILTINS_H

#include <octo/cll.h>

#include "mpc.h"
#include "ansh/parse.h"

typedef struct hashable_builtin_t {
    int(*func)(mpc_ast_t *cmd_ast, ...);
} hashable_builtin;

octo_dict_cll_t *builtins;

int add_builtin(const char *const key,
        int(*builtin_func)(mpc_ast_t *cmd_ast, ...));
void build_builtins();
int is_builtin(mpc_ast_t *cmd_ast);
int run_builtin(mpc_ast_t *cmd_ast);

// Builtin functions
int builtin_set(mpc_ast_t *cmd_ast, ...);
int builtin_echo(mpc_ast_t *cmd_ast, ...);

#endif

