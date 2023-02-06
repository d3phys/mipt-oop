#ifndef WORD_H_
#define WORD_H_
#include <stdint.h>
#include <stdlib.h>

typedef uint64_t rank_t;

struct word_vtbl;
struct word_base
{
    char* data;
    size_t len;
    word_vtbl* vptr;
};

struct word_vtbl
{
    word_base* (*parse)(const char* input);
    void (*free)(word_base *word);
    rank_t (*rank)(const word_base *word);
};

#endif /* WORD_H_ */
