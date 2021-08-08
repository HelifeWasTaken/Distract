/*
** EPITECH PROJECT, 2021
** set_distract_animable_frame
** File description:
** Source code
*/

#include "distract/animable.h"

int get_distract_animable_frame(distract_animable_t *distract_animable)
{
    return (distract_animable->current_sheet_frame
        - distract_animable->info.distract_animations[distract_animable->current_distract_anim].start_id);
}
