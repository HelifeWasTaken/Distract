/*
** EPITECH PROJECT, 2021
** mouse
** File description:
** MOUSE
*/

#include "distract/game.h"

sfVector2f get_mouse_pos(sfRenderWindow *window, sfView *view)
{
    return (sfRenderWindow_mapPixelToCoords(window,
        sfMouse_getPositionRenderWindow(window),
        view));
}