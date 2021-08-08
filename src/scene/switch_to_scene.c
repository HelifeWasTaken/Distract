/*
** EPITECH PROJECT, 2020
** load_distract_scene
** File description:
** Source code
*/

#include "distract/game.h"
#include "distract/util.h"

void switch_to_distract_scene(game_t *game, int id)
{
    game->distract_scene->in_exit_state = true;
    game->distract_scene->pending_distract_scene_id = id;
}