/*
** EPITECH PROJECT, 2020
** distract_resource
** File description:
** Source code
*/

#include <stdio.h>
#include "distract/debug.h"
#include "distract/game.h"
#include "distract/resources.h"
#include "distract/hashmap.h"
#include "distract/util.h"
#include "stdlib.h"

int distract_util_strcmp(char const *s1, char const *s2);

distract_resource_t *create_distract_resource(game_t *game, char *file, enum distract_resource_type type)
{
    distract_resource_t *distract_resource = malloc(sizeof(distract_resource_t));

    if (file == NULL || distract_resource == NULL) {
        fprintf(stderr, "Failed to init distract_resource");
        return (NULL);
    }
    distract_resource->type = type;
    distract_resource->path = strdup(file);
    if (distract_resource->path == NULL) {
        free(distract_resource);
        return (NULL);
    }
    if (distract_hashmap_set(&game->distract_scene->distract_resources, distract_resource->path, distract_resource) < 0) {
        free(distract_resource);
        fprintf(stderr, "Failed to set in distract_hashmap distract_resource");
        return (NULL);
    }
    return (distract_resource);
}

distract_resource_t *get_distract_resource(game_t *game, char *file)
{
    return (distract_hashmap_get(game->distract_scene->distract_resources, file));
}

void destroy_distract_resource_asset(distract_resource_t *distract_resource)
{
    switch(distract_resource->type) {
        case DR_TEXTURE: SAFE_RESOURCE_DESTROY(sfTexture_destroy,
            distract_resource->texture);
            break;
        case DR_SOUND: SAFE_RESOURCE_DESTROY(sfSound_destroy, distract_resource->distract_sound);
            break;
        case DR_SOUND_BUFFER: SAFE_RESOURCE_DESTROY(sfSoundBuffer_destroy,
            distract_resource->distract_sound_buffer);
            break;
        case DR_MUSIC: SAFE_RESOURCE_DESTROY(sfMusic_destroy, distract_resource->distract_music);
            break;
        case DR_FONT: SAFE_RESOURCE_DESTROY(sfFont_destroy, distract_resource->font);
            break;
        case DR_VERTEX: SAFE_RESOURCE_DESTROY(sfVertexArray_destroy,
            distract_resource->vao);
            break;
        default: fprintf(stderr, "Unknown asset");
            break;
    }
}

void destroy_distract_resource(game_t *game, distract_resource_t *distract_resource)
{
    if (distract_resource == NULL)
        return;
    distract_hashmap_unset(&game->distract_scene->distract_resources, distract_resource->path);
    destroy_distract_resource_asset(distract_resource);
    if (distract_resource->path)
        free(distract_resource->path);
    free(distract_resource);
}

void destroy_distract_resource_by_name(game_t *game, char *file)
{
    destroy_distract_resource(game, get_distract_resource(game, file));
}
