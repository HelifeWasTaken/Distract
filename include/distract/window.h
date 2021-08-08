/*
** EPITECH PROJECT, 2020
** window
** File description:
** Source code
*/

#ifndef DISTRACT_WINDOW_H
#define DISTRACT_WINDOW_H
#include "SFML/Graphics.h"

#define MODE(width, height, depth) \
    (sfVideoMode) { width, height, depth }

#define DEFAULT_RENDERSTATE(shader) \
    (sfRenderStates) { sfBlendAlpha, sfTransform_Identity, NULL, shader }

/**
 * @brief Create a standard window object
 *
 * @param mode The video mode of the window
 * @param title The title of the window
 * @return sfRenderWindow*
 */
sfRenderWindow *create_standard_window(sfVideoMode mode, char const *title);

#endif //DISTRACT_WINDOW_H