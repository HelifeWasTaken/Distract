/*
** EPITECH PROJECT, 2020
** is_distract_scene_updated
** File description:
** Source code
*/

#include "distract/game.h"

bool is_distract_scene_updated(game_t *game)
{
    return (sfRenderWindow_isOpen(game->window)
        && !game->distract_scene->in_exit_state
        && !game->is_closing);
}