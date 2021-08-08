/*
** EPITECH PROJECT, 2021
** distract
** File description:
** distract_hashmap
*/

#include "stdlib.h"
#include "distract/hashmap.h"

static void free_buckets(struct distract_hashmap_list *bucket)
{
    if (bucket == NULL)
        return;
    free_buckets(bucket->next);
    free(bucket);
}

void distract_hashmap_destroy(distract_hashmap_t *map)
{
    if (map) {
        for (size_t i = 0; i < map->capacity; i++)
            free_buckets(map->bucket[i].data);
        free(map->bucket);
        free(map);
    }
}
