#ifndef WORD_TYPES_H_
#define WORD_TYPES_H_
#include <stdlib.h>
#include <string.h>
#include "word.h"

struct word_english
{
    word_base base;
    size_t is_american;
};

struct word_one_char
{
    word_base base;
};

void word_free(word_base* word);

word_base*  word_english_parse(const char* input);
word_base* word_one_char_parse(const char* input);

rank_t  word_english_rank(const word_base* word);
rank_t word_one_char_rank(const word_base* word);

static word_vtbl word_english_vtbl = {
    .parse = &word_english_parse,
    .free = &word_free,
    .rank = &word_english_rank,
};

static word_vtbl word_one_char_vtbl = {
    .parse = &word_one_char_parse,
    .free = &word_free,
    .rank = &word_one_char_rank,
};

#endif /* WORD_TYPES_H_ */

