#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <octo/cll.h>
#include <octo/keygen.h>

#include "mpc.h"
#include "ansh/ansh.h"

int main(int argc, char* argv[]) {
    if(argc == 1 || argv == NULL) {}
	octo_dict_cll_t *env_vars = setup();
	hashable_str *key_prompt = malloc(sizeof(hashable_str));
	memset(key_prompt, 0, sizeof(hashable_str));
	strcpy(key_prompt->str, "PROMPT");
	fprintf(stderr, "PROMPT: %s", (char *)(octo_cll_fetch(key_prompt, env_vars)));
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

	hashable_str *key_prompt = malloc(sizeof(hashable_str));
	memset(key_prompt, 0, sizeof(hashable_str));
	strcpy(key_prompt->str, "PROMPT");
	hashable_str *val_prompt = malloc(sizeof(hashable_str));
	memset(val_prompt, 0, sizeof(hashable_str));
	strcpy(val_prompt->str, "ansh $ ");
	if(octo_cll_insert(key_prompt, val_prompt, vars) != 0) {
		fprintf(stderr, "Error adding PROMPT variable during setup()\n");
		return NULL;
	}
	return vars;
}
