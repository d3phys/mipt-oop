#include <stdio.h>
#include <ctype.h>
#include "dict.h"
#include "word.h"
#include "word_types.h"

static void
skip_spaces(const char** input)
{
    while (**input && isspace(**input))
        (*input)++;
}

int main()
{
    printf("Hello\n");

    char buffer[0x100];
    fgets(buffer, sizeof(buffer), stdin);

    dictionary dict {};
    dict_ctor(&dict);

    const char *input = buffer;
    word_base* word = nullptr;
    do {
        skip_spaces(&input);
        word = dict_parse(&dict, input, &word_english_vtbl);
        if (word)
            input += word->len;
    } while (word);

    dict_print(&dict);

    dict_dtor(&dict);
    return 0;
}
