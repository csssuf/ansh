#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <octo/cll.h>
#include <octo/keygen.h>

#include "mpc.h"
#include "ansh/ansh.h"
#include "ansh/parse.h"
#include "ansh/util.h"

int main(int argc, char* argv[]) {
    if(argc == 1 || argv == NULL) {}
    setup_parser();
    octo_dict_cll_t *env_vars = setup();
    char *read_buffer;
    mpc_result_t parse_result;
    while(1) {
        read_buffer = readline((char *)(fetch_value("PROMPT", env_vars)));
        if(read_buffer == NULL) {
            break;
        }
        add_history(read_buffer);
        if(mpc_parse("input", read_buffer, parser_command, &parse_result)) {
            mpc_ast_print(parse_result.output);
            mpc_ast_delete(parse_result.output);
        } else {
            mpc_err_print(parse_result.error);
            mpc_err_delete(parse_result.error);
        }
    }
    free_parser();
    octo_cll_free(env_vars);
    return EXIT_SUCCESS;
}

octo_dict_cll_t *setup() {
    uint8_t *master_key = octo_keygen();
    octo_dict_cll_t *vars = octo_cll_init(
        ENV_INIT_OCTO_KEY_SIZE,
        ENV_INIT_OCTO_VAL_SIZE,
        ENV_INIT_OCTO_BUCKETS,
        master_key
    );

    if(insert_kv_pair("PROMPT", "ansh $ ", vars) != 0) {
        fprintf(stderr, "Error adding PROMPT variable during setup()\n");
        return NULL;
    }

    if(insert_kv_pair("PATH", "/bin:/usr/bin", vars) != 0) {
        fprintf(stderr, "Error adding PATH variable during setup()\n");
    }
    return vars;
}
