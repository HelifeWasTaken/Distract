/*
** EPITECH PROJECT, 2021
** distract_sound_emitter
** File description:
** Source code
*/

#ifndef DISTRACT_SOUND_H
#define DISTRACT_SOUND_H

#include "distract/hashmap.h"
#include "distract/resources.h"
#include "distract/util.h"
#include <SFML/Audio.h>
#include <SFML/Audio/Sound.h>
#include "stdlib.h"

typedef struct distract_sound_emitter {
    float volumes[32];
} distract_sound_emitter_t;

/**
 * @brief Create a distract sound emitter object
 *
 * @param game The game object
 * @return distract_sound_emitter_t*
 */
distract_sound_emitter_t *create_distract_sound_emitter(game_t *game);

/**
 * @brief destroy a distract sound emitter object
 *
 * @param emitter the emitter to destroy
 */
void destroy_distract_sound_emitter(distract_sound_emitter_t *emitter);

/**
 * @brief Get the distract sound volume object
 *
 * @param game
 * @param distract_sound_type the sound type
 * @return float
 */
float get_distract_sound_volume(game_t *game, unsigned char distract_sound_type);

/**
 * @brief Set the distract sound volume object
 *
 * @param game
 * @param distract_sound_type
 * @param percentage
 */
void set_distract_sound_volume(game_t *game, unsigned char distract_sound_type,
    float percentage);

/**
 * @brief Play a sound
 *
 * @param game
 * @param distract_sound_type
 * @param file the sound file
 * @return true if the sound was played, false otherwise
 * @return false if the sound was not played
 */
bool play_distract_sound(game_t *game, int distract_sound_type, char *file);

/**
 * @brief Play a music
 *
 * @param game
 * @param distract_sound_type
 * @param file
 * @return true if the music was played, false otherwise
 * @return false if the music was not played
 */
bool play_distract_music(game_t *game, int distract_sound_type, char *file);

#endif /* DISTRACT_SOUND_H */