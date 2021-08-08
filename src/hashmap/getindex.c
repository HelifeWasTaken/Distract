/*
** EPITECH PROJECT, 2021
** distract
** File description:
** index
*/

#include "stdlib.h"
#include "distract/hashmap.h"

void *distract_hashmap_getindex(distract_hashmap_t *map, void *key)
{
    struct distract_hashmap_list *list = map->bucket[
        map->hasher(map, key) % map->capacity].data;

    for (; list; list = list->next)
        if (strcmp(key, list->key) == 0)
            return (list->value);
    return (NULL);
}
