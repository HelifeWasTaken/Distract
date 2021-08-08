/*
** EPITECH PROJECT, 2020
** set_pending_distract_scene
** File description:
** Source code
*/
#include "distract/scene.h"

void set_pending_distract_scene(game_t *game, int id)
{
    game->distract_scene->pending_distract_scene_id = id;
}
