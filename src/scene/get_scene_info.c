/*
** EPITECH PROJECT, 2020
** get_distract_scene_info
** File description:
** Source code
*/
#include "distract/game.h"
#include "distract/scene.h"

distract_scene_info_t *get_distract_scene_info(game_t *game, int id)
{
    distract_scene_info_t *distract_scene = game->distract_scenes;

    for (; distract_scene != NULL; distract_scene = distract_scene->next) {
        if (distract_scene->id == id)
            return (distract_scene);
    }
    return (NULL);
}
