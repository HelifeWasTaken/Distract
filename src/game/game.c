/*
** EPITECH PROJECT, 2020
** game
** File description:
** Source code
*/

#include "distract/game.h"
#include "distract/entity.h"
#include "distract/hashmap.h"
#include "distract/sound.h"
#include "stdlib.h"
#include "distract/debug.h"
#include "distract/util.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/View.h>

game_t *create_game(void)
{
    game_t *game = calloc(1, sizeof(game_t));

    game->distract_sound = create_distract_sound_emitter(game);
    game->distract_scene = allocate_distract_scene();
    if (game == NULL || game->distract_sound == NULL || game->distract_scene == NULL) {
        fprintf(stderr, "Game initialisation failed");
        return (NULL);
    }
    return (game);
}

void set_game_view(game_t *game, sfView *view)
{
    game->view = view;
    sfRenderWindow_setView(game->window, view);
}

static void destroy_entity_infos(game_t *game)
{
    entity_info_t *entity_info = game->entities;
    entity_info_t *next = NULL;

    while (entity_info != NULL) {
        next = entity_info->next;
        free(entity_info);
        entity_info = next;
    }
    game->entities = NULL;
}

static void destroy_distract_scene_infos(game_t *game)
{
    distract_scene_info_t *distract_scene_info = game->distract_scenes;
    distract_scene_info_t *next = NULL;

    while (distract_scene_info != NULL) {
        next = distract_scene_info->next;
        free(distract_scene_info);
        distract_scene_info = next;
    }
    game->distract_scenes = NULL;
}

void destroy_game(game_t *game)
{
    if (game == NULL)
        return;
    if (game->window != NULL)
        sfRenderWindow_destroy(game->window);
    destroy_distract_scene(game, true);
    deallocate_distract_scene(game->distract_scene);
    destroy_distract_sound_emitter(game->distract_sound);
    destroy_entity_infos(game);
    destroy_distract_scene_infos(game);
    free(game);
}
