#ifndef ANSH_UTIL_H
#define ANSH_UTIL_H

#include <octo/cll.h>
#include "ansh/ansh.h"

int insert_kv_pair(const char *const key, const char *const value, octo_dict_cll_t *dict);
void *fetch_value(const char *const key, octo_dict_cll_t *dict);

#endif
