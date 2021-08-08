/*
** EPITECH PROJECT, 2020
** load_pending_distract_scene
** File description:
** Source code
*/
#include "distract/scene.h"

int load_pending_distract_scene(game_t *game)
{
    int id = game->distract_scene->pending_distract_scene_id;
    distract_scene_info_t *distract_scene_info = get_distract_scene_info(game, id);

    game->is_paused = false;
    game->distract_scene->id = id;
    game->distract_scene->info = distract_scene_info;
    game->distract_scene->in_exit_state = false;
    game->distract_scene->pending_distract_scene_id = -1;
    return (distract_scene_info->lifecycle(game));
}
