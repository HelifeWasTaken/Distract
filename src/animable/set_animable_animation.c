/*
** EPITECH PROJECT, 2021
** set_distract_animable_distract_animation
** File description:
** Source code
*/

#include "distract/animable.h"

void set_distract_animable_distract_animation(distract_animable_t *distract_animable, int id)
{
    distract_animable->current_distract_anim = id;
    set_distract_animable_frame(distract_animable, 0);
}
