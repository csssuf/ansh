#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <octo/cll.h>
#include <octo/keygen.h>

#include "ansh/builtins.h"
#include "ansh/ansh.h"
#include "mpc.h"

int add_builtin(const char *const key,
                 int(*builtin_func)(mpc_ast_t *cmd_ast, ...)) {
    hashable_str *hashable_key = malloc(sizeof(hashable_str));
    memset(hashable_key, 0, sizeof(hashable_str));
    strcpy(hashable_key->str, key);
    hashable_builtin *h_builtin = malloc(sizeof(hashable_builtin));
    h_builtin->func = builtin_func;
    return octo_cll_insert(hashable_key, h_builtin, builtins);
}

void build_builtins() {
    builtins = octo_cll_init(
            ENV_INIT_OCTO_KEY_SIZE,
            ENV_INIT_OCTO_VAL_SIZE,
            ENV_INIT_OCTO_BUCKETS,
            octo_keygen());

    add_builtin("set", &builtin_set);
    add_builtin("echo", &builtin_echo);
}

int is_builtin(mpc_ast_t *cmd_ast) {
    mpc_ast_t *expr_tree = cmd_ast->children[1];
    return strstr(expr_tree->tag, "builtin") != NULL ||
           (strstr(expr_tree->tag, ">") != NULL && 
            strstr(expr_tree->children[0]->tag, "builtin") != NULL);
}

int run_builtin(mpc_ast_t *cmd_ast) {
    mpc_ast_t *expr_tree = cmd_ast->children[1];
    if(expr_tree->children_num > 0) {
        mpc_ast_t *builtin_expr = expr_tree->children[0];
        hashable_str *h_key = malloc(sizeof(hashable_str));
        memset(h_key, 0, sizeof(hashable_str));
        strcpy(h_key->str, builtin_expr->contents);
        ((int (*)(mpc_ast_t *, ...))octo_cll_fetch(h_key, builtins)) (cmd_ast);
    } else {
        fprintf(stderr, "builtin: %s\n", expr_tree->contents);
    }
    return -1;
}

int builtin_set(mpc_ast_t *cmd_ast, ...) { fprintf(stderr, "set called\n"); if(cmd_ast != NULL) { return 0; } return 1;}
int builtin_echo(mpc_ast_t *cmd_ast, ...) { fprintf(stderr, "echo called\n"); if(cmd_ast != NULL) { return 0; } return 1; }

