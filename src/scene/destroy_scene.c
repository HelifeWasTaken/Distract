/*
** EPITECH PROJECT, 2021
** push_distract_scene
** File description:
** Source code
*/

#include "distract/game.h"
#include "distract/entity.h"
#include "distract/hashmap.h"
#include "distract/resources.h"
#include "distract/debug.h"
#include "stdlib.h"

static void destroy_distract_scene_entities(game_t *game)
{
    entity_t *entity = game->distract_scene->entities;
    entity_t *next = NULL;

    while (entity != NULL) {
        next = entity->next;
        destroy_entity(game, entity);
        entity = next;
    }
    game->distract_scene->entities = NULL;
}

static void destroy_distract_scene_distract_resources(game_t *game)
{
    distract_hashmap_t *map = game->distract_scene->distract_resources;
    struct distract_hashmap_list *list = NULL;

    if (map == NULL)
        return;
    for (size_t i = 0; i < map->capacity; i++) {
        list = map->bucket[i].data;
        for (; list; list = list->next)
            destroy_distract_resource(game, list->value);
    }
    game->distract_scene->distract_resources = distract_hashmap_create(map->capacity / 2, map->hasher);
    if (game->distract_scene->distract_resources == NULL)
        fprintf(stderr, "Hashmap create failed in destroy distract_scene ressources");
    distract_hashmap_destroy(map);
}

void destroy_distract_scene(game_t *game, bool destroy_distract_resources)
{
    if (game->distract_scene)
        destroy_distract_scene_entities(game);
    if (destroy_distract_resources)
        destroy_distract_scene_distract_resources(game);
}
