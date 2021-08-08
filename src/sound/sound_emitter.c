/*
** EPITECH PROJECT, 2021
** distract_sound_emitter
** File description:
** Source code
*/

#include <SFML/Audio.h>
#include <SFML/Audio/Music.h>
#include <SFML/Audio/Types.h>
#include "distract/game.h"
#include "distract/sound.h"
#include "distract/resources.h"

distract_sound_emitter_t *create_distract_sound_emitter(game_t *game UNUSED)
{
    distract_sound_emitter_t *emitter = calloc(1, sizeof(distract_sound_emitter_t));

    if (emitter == NULL)
        return (NULL);
    for (int i = 0; i < 32; i++) {
        emitter->volumes[i] = 100;
    }
    return (emitter);
}

void set_distract_sound_volume(game_t *game, unsigned char distract_sound_type,
    float percentage)
{
    game->distract_sound->volumes[distract_sound_type] = percentage;
}

float get_distract_sound_volume(game_t *game, unsigned char distract_sound_type)
{
    return game->distract_sound->volumes[distract_sound_type];
}

bool play_distract_sound(game_t *game, int distract_sound_type, char *file)
{
    distract_sound_emitter_t *emitter = game->distract_sound;
    float volume = distract_sound_type == -1 ? 100 : emitter->volumes[distract_sound_type];
    sfSound *distract_sound = create_distract_sound(game, file);

    if (distract_sound == NULL)
        return (false);
    sfSound_setVolume(distract_sound, volume);
    sfSound_play(distract_sound);
    return (true);
}

bool play_distract_music(game_t *game, int distract_sound_type, char *file)
{
    distract_sound_emitter_t *emitter = game->distract_sound;
    float volume = distract_sound_type == -1 ? 100 : emitter->volumes[distract_sound_type];
    sfMusic *distract_music = create_distract_music(game, file);

    if (distract_music == NULL)
        return (false);
    sfMusic_setLoop(distract_music, true);
    sfMusic_setVolume(distract_music, volume);
    sfMusic_play(distract_music);
    return (true);
}
