/*
** EPITECH PROJECT, 2020
** MY_RPG_PUBLIC
** File description:
** destroy_distract_sound_emitter.c
*/

#include "distract/sound.h"

void destroy_distract_sound_emitter(distract_sound_emitter_t *emitter)
{
    free(emitter);
}
