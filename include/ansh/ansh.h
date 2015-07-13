#ifndef ANSH_ANSH_H
#define ANSH_ANSH_H

#define ENV_INIT_OCTO_KEY_SIZE	32
#define ENV_INIT_OCTO_VAL_SIZE	256
#define ENV_INIT_OCTO_BUCKETS	16

#include <octo/cll.h>

typedef struct hashable_str_s {
	char str[ENV_INIT_OCTO_KEY_SIZE];
} hashable_str;

octo_dict_cll_t *setup();

#endif //ANSH_ANSH_H
