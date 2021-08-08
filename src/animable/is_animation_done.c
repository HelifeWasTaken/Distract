/*
** EPITECH PROJECT, 2021
** is_distract_animation_done
** File description:
** Source code
*/

#include "distract/animable.h"

bool is_distract_animation_done(distract_animable_t *distract_animable)
{
    return (distract_animable->current_sheet_frame
        == distract_animable->info.distract_animations[distract_animable->current_distract_anim].end_id);
}
