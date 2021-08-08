/*
** EPITECH PROJECT, 2020
** distract_sound
** File description:
** Source code
*/

#include "distract/game.h"
#include "distract/debug.h"
#include "distract/resources.h"
#include "SFML/Graphics.h"
#include "distract/util.h"
#include "stdio.h"
#include "stdarg.h"
#include <stdlib.h>

static char *get_sb_filepath(char *filepath)
{
    char *sb_filepath = malloc(sizeof(char) * (strlen(filepath) + 1));
    int i = 0;

    if (sb_filepath == NULL)
        return (NULL);
    for (i = 0; filepath[i] != '\0'; i++) {
        sb_filepath[i] = filepath[i];
    }
    sb_filepath[i++] = 's';
    sb_filepath[i++] = 'b';
    sb_filepath[i] = '\0';
    return (sb_filepath);
}

sfSound *create_distract_sound(game_t *game, char *filepath)
{
    distract_resource_t *distract_resource = get_distract_resource(game, filepath);
    sfSound *tmp;

    if (distract_resource == NULL) {
        if ((tmp = sfSound_create()) == NULL) {
            fprintf(stderr, "Failed to init distract_sound");
            return (NULL);
        }
        distract_resource = create_distract_resource(game, get_sb_filepath(filepath),
            DR_SOUND_BUFFER);
        if (distract_resource == NULL)
            return (NULL);
        distract_resource->distract_sound_buffer = sfSoundBuffer_createFromFile(filepath);
        sfSound_setBuffer(tmp, distract_resource->distract_sound_buffer);
        distract_resource = create_distract_resource(game, filepath, DR_SOUND);
        if (distract_resource == NULL)
            return (NULL);
        distract_resource->distract_sound = tmp;
    }
    return (distract_resource->distract_sound);
}

sfMusic *create_distract_music(game_t *game, char *filepath)
{
    distract_resource_t *distract_resource = get_distract_resource(game, filepath);

    if (distract_resource == NULL) {
        distract_resource = create_distract_resource(game, filepath, DR_MUSIC);
        if (distract_resource == NULL)
            return (NULL);
        if ((distract_resource->distract_music = sfMusic_createFromFile(filepath)) == NULL)
            fprintf(stderr, "Failed to init distract_music");
    }
    return (distract_resource->distract_music);
}
