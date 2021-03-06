/*
** EPITECH PROJECT, 2020
** entity
** File description:
** Entity
*/
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/graphics.h"
#include "distract/math.h"
#include "SFML/Window.h"
#include "SFML/Graphics.h"

sfVector2f move_entity_towards(entity_t *entity, sfVector2f target,
    float distance)
{
    sfVector2f movement = v2fnormalized(pv2fsub(&target, &entity->pos));

    pv2fadd(&entity->pos, pv2fmulf(&movement, distance));
    return movement;
}
