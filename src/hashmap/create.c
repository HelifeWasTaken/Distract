/*
** EPITECH PROJECT, 2021
** distract
** File description:
** create
*/

#include <stdio.h>
#include "stdlib.h"
#include <distract/hashmap.h>
#include <distract/util.h>
#include <distract/debug.h>

static size_t no_hashing_fnc(distract_hashmap_t *map, void *key)
{
    return (((size_t) key) % map->capacity);
}

distract_hashmap_t *distract_hashmap_create(size_t capacity,
    size_t (*hasher)(distract_hashmap_t *map, void *key))
{
    distract_hashmap_t *map = calloc(1, sizeof(distract_hashmap_t));

    if (map == NULL) {
        fprintf(stderr, "Hashmap ressource could not be initted");
        return (NULL);
    }
    if (capacity < 2)
        capacity = 2;
    map->capacity = capacity;
    map->size = 0;
    map->bucket = calloc(capacity, sizeof(struct distract_hashmap_bucket));
    if (map->bucket == NULL) {
        fprintf(stderr, "Buckets and could not be initted");
        return (NULL);
    }
    map->hasher = hasher != NULL ? hasher : &no_hashing_fnc;
    return (map);
}
