/*
** EPITECH PROJECT, 2021
** set_distract_animable_frame
** File description:
** Source code
*/

#include "distract/animable.h"
#include "distract/debug.h"
#include "distract/def.h"
#include <SFML/Graphics.h>
#include <stdio.h>

void set_distract_animable_frame(distract_animable_t *distract_animable, int id)
{
    if (distract_animable->info.frames_per_line == 0) {
        fprintf(stderr, "Animable have an invalid frames per line!");
        return;
    }
    distract_animable->current_sheet_frame
        = distract_animable->info.distract_animations[distract_animable->current_distract_anim].start_id + id;
    sfSprite_setTextureRect(distract_animable->info.sprite, IRECT(
        (distract_animable->current_sheet_frame % distract_animable->info.frames_per_line)
            * distract_animable->info.frame_size.x,
        (distract_animable->current_sheet_frame / distract_animable->info.frames_per_line)
            * distract_animable->info.frame_size.y,
        distract_animable->info.frame_size.x, distract_animable->info.frame_size.y));
}
