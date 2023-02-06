#ifndef DICT_H_
#define DICT_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdint.h>
#include "word.h"

struct linked_list
{
    linked_list* next;
    word_base* word;
};

typedef unsigned long hash_t;
typedef hash_t (*hash_func)(unsigned char* data);

struct dictionary
{
    linked_list* slots;
    hash_func hash;
    size_t capacity;
};

hash_t hash_djb2(unsigned char *str);

dictionary* dict_ctor(dictionary* dict, size_t capacity = 0x100, hash_func hash = hash_djb2);
void dict_dtor(dictionary* dict);
void dict_print(dictionary* dict);

word_base* dict_add(dictionary* dict, word_base* word);
word_base* dict_parse(dictionary* dict, const char* input, word_vtbl* vtbl);

word_base* dict_find(dictionary* dict, word_base* word);

#endif /* DICT_H_ */
