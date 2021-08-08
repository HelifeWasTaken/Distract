/*
** EPITECH PROJECT, 2021
** push_distract_scene
** File description:
** Source code
*/

#include "distract/game.h"
#include "distract/resources.h"
#include "distract/scene.h"
#include "distract/sound.h"
#include <stdio.h>

static void pause_distract_music(distract_scene_t *parent_distract_scene)
{
    distract_hashmap_t *distract_hashmap = parent_distract_scene->distract_resources;
    struct distract_hashmap_list *list = NULL;
    distract_resource_t *distract_resources = NULL;;

    for (size_t i = 0; i < parent_distract_scene->distract_resources->capacity; i++) {
        list = distract_hashmap->bucket[i].data;
        if (list == NULL)
            continue;
        distract_resources = list->value;
        if (distract_resources->type == DR_MUSIC)
            sfMusic_pause(distract_resources->distract_music);
        else if (distract_resources->type == DR_SOUND)
            sfSound_pause(distract_resources->distract_sound);
    }
}

static void resume_distract_music(game_t *game, distract_scene_t *parent_distract_scene)
{
    distract_hashmap_t *distract_hashmap = parent_distract_scene->distract_resources;
    struct distract_hashmap_list *list = NULL;
    distract_resource_t *distract_resources = NULL;;

    for (size_t i = 0; i < parent_distract_scene->distract_resources->capacity; i++) {
        list = distract_hashmap->bucket[i].data;
        if (list == NULL)
            continue;
        distract_resources = list->value;
        if (distract_resources->type == DR_MUSIC) {
            sfMusic_setVolume(distract_resources->distract_music, game->distract_sound->volumes[0]);
            sfMusic_play(distract_resources->distract_music);
        }
    }
}

int await_distract_scene(game_t *game, int distract_scene_id)
{
    int code;
    distract_scene_t *parent_distract_scene = game->distract_scene;

    pause_distract_music(parent_distract_scene);
    game->distract_scene = allocate_distract_scene();
    if (game->distract_scene == NULL)
        return (-1);
    set_pending_distract_scene(game, distract_scene_id);
    reset_game_events(game);
    code = load_pending_distract_scene(game);
    deallocate_distract_scene(game->distract_scene);
    reset_game_events(game);
    game->distract_scene = parent_distract_scene;
    resume_distract_music(game, parent_distract_scene);
    return (code);
}
