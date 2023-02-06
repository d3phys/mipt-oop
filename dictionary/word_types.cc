#include "word_types.h"
#include <ctype.h>

void
word_free(word_base* word)
{
    free(word->data);
}

static size_t
word_len(const char* str)
{
    size_t len = 0;
    while (*str && !isspace(*str)) {
        str++;
        len++;
    }

    return len;
}

word_base*
word_one_char_parse(const char* input)
{
    size_t len = word_len(input);
    if (len == 0)
        return nullptr;

    word_one_char *self = (word_one_char*)calloc(1, sizeof(word_one_char));
    self->base.data = (char*)calloc(2, sizeof(char));
    self->base.len = 1;
    self->base.vptr = &word_one_char_vtbl;
    return (word_base*)self;
}

rank_t
word_one_char_rank(const word_base* word)
{
    const word_one_char* self = (const word_one_char *)word;
    return (rank_t)(*self->base.data);
}

word_base*
word_english_parse(const char* input)
{
    size_t len = word_len(input);
    if (len == 0)
        return nullptr;

    word_english *self = (word_english*)calloc(1, sizeof(word_english));
    self->base.data = (char*)calloc(len + 1, sizeof(char));
    memcpy(self->base.data, input, len);

    self->base.len = len;
    self->base.vptr = &word_english_vtbl;
    return (word_base*)self;
}

rank_t
word_english_rank(const word_base* word)
{
    const word_english* self = (const word_english *)word;

    rank_t rank = 0;
    size_t len = strlen(self->base.data);
    for (size_t i = 0; i != len; ++i)
        rank += (rank_t)self->base.data[i];

    return rank;
}
