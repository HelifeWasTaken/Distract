/*
** EPITECH PROJECT, 2021
** allocate_distract_scene
** File description:
** Source code
*/

#include <stdio.h>
#include "distract/debug.h"
#include "distract/scene.h"
#include "distract/util.h"
#include <stdlib.h>

static size_t hash_distract_resource_key(distract_hashmap_t *map, void *key)
{
    char *str = (void *)key;
    size_t hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return (hash % map->capacity);
}

distract_scene_t *allocate_distract_scene(void)
{
    distract_scene_t *distract_scene = calloc(1, sizeof(distract_scene_t));

    if (!distract_scene)
        return (NULL);
    distract_scene->distract_resources = distract_hashmap_create(50, &hash_distract_resource_key);
    distract_scene->id = -1;
    distract_scene->pending_distract_scene_id = -1;
    if (distract_scene->distract_resources == NULL) {
        fprintf(stderr, "Entity distract_hashmap ressource could not be initted");
        return (NULL);
    }
    return (distract_scene);
}

void deallocate_distract_scene(distract_scene_t *distract_scene)
{
    distract_hashmap_destroy(distract_scene->distract_resources);
    free(distract_scene);
}
