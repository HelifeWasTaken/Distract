/*
** EPITECH PROJECT, 2020
** add_distract_scene
** File description:
** Source code
*/

#include <stdio.h>
#include "distract/game.h"
#include "distract/scene.h"
#include "stdlib.h"
#include "stdarg.h"
#include "distract/debug.h"

bool register_distract_scene(game_t *game, int id, int (*lifecycle)(game_t *game))
{
    distract_scene_info_t *distract_scene = malloc(sizeof(distract_scene_t));

    if (distract_scene == NULL) {
        fprintf(stderr, "Failed to init register distract_scene");
        return (false);
    }
    distract_scene->id = id;
    distract_scene->lifecycle = lifecycle;
    distract_scene->next = game->distract_scenes;
    game->distract_scenes = distract_scene;
    return (true);
}
