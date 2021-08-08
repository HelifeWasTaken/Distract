/*
** EPITECH PROJECT, 2021
** distract
** File description:
** get
*/

#include "distract/hashmap.h"

void *distract_hashmap_get(distract_hashmap_t *map, void *key)
{
    return (distract_hashmap_getindex(map, key));
}
