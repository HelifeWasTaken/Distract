/*
** EPITECH PROJECT, 2021
** set_entity_z
** File description:
** Source code
*/

#include "distract/debug.h"
#include "distract/game.h"
#include "distract/entity.h"
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "stdarg.h"

static void add_between(entity_t *prev, entity_t *next, entity_t *entity)
{
    entity->next = next;
    entity->prev = prev;
    prev->next = entity;
    if (next != NULL)
        next->prev = entity;
}

void add_to_entities(game_t *game, entity_t *entity)
{
    distract_scene_t *distract_scene = game->distract_scene;
    entity_t *c = game->distract_scene->entities;
    entity_t *prev;

    if (c == NULL || c->z >= entity->z) {
        entity->next = distract_scene->entities;
        if (entity->next != NULL)
            entity->next->prev = entity;
        distract_scene->entities = entity;
        return;
    }
    for (; c != NULL; c = c->next) {
        if (c->z >= entity->z)
            break;
        prev = c;
    }
    add_between(prev, c, entity);
}