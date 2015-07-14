#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <octo/cll.h>
#include <octo/keygen.h>

#include "mpc.h"
#include "ansh/ansh.h"
#include "ansh/util.h"

int main(int argc, char* argv[]) {
    if(argc == 1 || argv == NULL) {}
    octo_dict_cll_t *env_vars = setup();
    hashable_str *key_prompt = malloc(sizeof(hashable_str));
    memset(key_prompt, 0, sizeof(hashable_str));
    strcpy(key_prompt->str, "PROMPT");
    fprintf(stderr, "PROMPT: %s", (char *)(octo_cll_fetch(key_prompt, env_vars)));
    free(key_prompt);
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
