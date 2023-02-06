#include "dict.h"

static void
list_free(linked_list* list)
{
    if (list->next)
        list_free(list->next);

    if (list->word) {
        list->word->vptr->free(list->word);
        free(list->word);
    }

    free(list->next);

    list->word = nullptr;
    list->next = nullptr;
}

hash_t
hash_djb2(unsigned char *str)
{
    hash_t hash = 5381;

    int c = 0;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

dictionary*
dict_ctor(dictionary* dict,
          size_t capacity,
          hash_func hash)
{
    assert(dict);

    linked_list* slots = (linked_list*)calloc(capacity, sizeof(linked_list));
    if (slots == nullptr)
         return perror("failed to create dictionary"), nullptr;

    dict->capacity = capacity;
    dict->slots = slots;

    return dict;
}

void
dict_dtor(dictionary* dict)
{
    assert(dict);

    for (size_t i = 0; i != dict->capacity; ++i)
        list_free(dict->slots + i);

    free(dict->slots);
    dict->slots = nullptr;
    dict->capacity = 0;
}

word_base*
dict_add(dictionary* dict,
         word_base* word)
{
    hash_t hash = word->vptr->rank(word);

    linked_list* slot = &dict->slots[hash % dict->capacity];
    while (slot->next)
        slot = slot->next;

    slot->next = (linked_list*)calloc(1, sizeof(linked_list));
    if (slot->next == nullptr)
         return perror("failed to allocate list"), nullptr;

    return slot->word = word;
}

word_base*
dict_find(dictionary* dict,
          word_base* word)
{
    hash_t hash = dict->hash((unsigned char*)word->data);
    linked_list* slot = &dict->slots[hash % dict->capacity];

    rank_t rank = word->vptr->rank(word);
    while (slot->word->vptr->rank(word) != rank) {
        slot = slot->next;
        if (slot == nullptr)
            break;
    }

    return slot->word;
}

word_base*
dict_parse(dictionary* dict,
           const char* input,
           word_vtbl* vtbl)
{
    word_base* word = vtbl->parse(input);
    if (word == nullptr)
        return nullptr;

    fprintf(stderr, "dict_parse: %s\n", word->data);

    return dict_add(dict, word);
}

void
dict_print(dictionary* dict)
{
    for (size_t i = 0; i != dict->capacity; ++i) {
        linked_list* slot = &dict->slots[i];
        while (slot->word) {
            printf("%s\n", slot->word->data);
            slot = slot->next;
        }
    }
}

