/*
** EPITECH PROJECT, 2021
** distract
** File description:
** set
*/

#include <stdio.h>
#include "stdlib.h"
#include "distract/hashmap.h"
#include "distract/debug.h"

int distract_hashmap_set(distract_hashmap_t **self, void *key, void *value)
{
    size_t index = (*self)->hasher(*self, key) % (*self)->capacity;

    if (distract_hashmap_get(*self, key) != NULL) {
        fprintf(stderr, "Called distract_hashmap set with a key already existing");
        return (-1);
    }
    if (insert_distract_hashmap_bucket_front(&(*self)->bucket[index].data,
                    &(struct distract_hashmap_list){key, value, NULL}) == false) {
        fprintf(stderr, "Could not insert in distract_hashmap");
        return (-1);
    }
    (*self)->size++;
    return (check_need_resize_distract_hashmap(self));
}
