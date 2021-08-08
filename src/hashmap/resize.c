/*
** EPITECH PROJECT, 2021
** distract
** File description:
** resize
*/

#include "stdlib.h"
#include <stdio.h>
#include "distract/hashmap.h"
#include "distract/debug.h"

bool check_need_resize_distract_hashmap(distract_hashmap_t **self)
{
    struct distract_hashmap_list *current = NULL;
    unsigned int count = 0;

    for (size_t i = 0; i < (*self)->capacity; i++) {
        count = 0;
        current = (*self)->bucket[i].data;
        for (; current; current = current->next)
            count++;
        if ((count > 2 && ((*self)->size >= (*self)->capacity / 2)) ||
                count > 3)
            return (distract_hashmap_resize(self));
    }
    return (true);
}

static bool distract_hashmap_resize_internal(distract_hashmap_t **self,
        struct distract_hashmap_bucket **new, size_t i)
{
    struct distract_hashmap_list *current = (*self)->bucket[i].data;
    size_t id = 0;
    struct distract_hashmap_list *nxt = NULL;

    while (current != NULL) {
        nxt = current->next;
        id = (*self)->hasher(*self, current->key) % (*self)->capacity;
        if (insert_distract_hashmap_bucket_front(&(*new)[id].data, current) == false)
            return (false);
        free(current);
        current = NULL;
        current = nxt;
    }
    return (true);
}

int distract_hashmap_resize(distract_hashmap_t **self)
{
    struct distract_hashmap_bucket *n_buck = NULL;
    size_t original_size = (*self)->capacity;

    (*self)->capacity *= 2;
    n_buck = calloc(sizeof(struct distract_hashmap_bucket), (*self)->capacity);
    if (n_buck == NULL) {
        fprintf(stderr, "Could not resize distract_hashmap");
        return (-1);
    }
    for (size_t i = 0; i < original_size; i++)
        if (distract_hashmap_resize_internal(self, &n_buck, i) == false) {
            fprintf(stderr, "Could not resize distract_hashmap");
            return (-1);
        }
    free((*self)->bucket);
    (*self)->bucket = n_buck;
    return (check_need_resize_distract_hashmap(self));
}
