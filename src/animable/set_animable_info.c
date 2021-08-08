/*
** EPITECH PROJECT, 2021
** set_distract_animable_info
** File description:
** Source code
*/

#include "distract/animable.h"

void set_distract_animable_info(distract_animable_t *distract_animable, distract_animable_info_t *info)
{
    distract_animable->info = *info;
    set_distract_animable_distract_animation(distract_animable, 0);
}
