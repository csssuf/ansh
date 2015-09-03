#include <stdlib.h>
#include <string.h>

#include "ansh/util.h"

int insert_kv_pair(const char *const key, const char *const value, octo_dict_cll_t *dict) {
    hashable_str *hashable_key = malloc(sizeof(hashable_str));
    memset(hashable_key, 0, sizeof(hashable_str));
    strcpy(hashable_key->str, key);
    hashable_str *hashable_value = malloc(sizeof(hashable_str));
    memset(hashable_value, 0, sizeof(hashable_str));
    strcpy(hashable_value->str, value);
    return octo_cll_insert(hashable_key, hashable_value, dict);
}

void *fetch_value(const char *const key, octo_dict_cll_t *dict) {
    hashable_str *hashable_key = malloc(sizeof(hashable_str));
    memset(hashable_key, 0, sizeof(hashable_str));
    strcpy(hashable_key->str, key);
    void *value = octo_cll_fetch(hashable_key, dict);
    free(hashable_key);
    return value;
}

