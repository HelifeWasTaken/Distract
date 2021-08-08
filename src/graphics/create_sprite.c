/*
** EPITECH PROJECT, 2020
** create_sprite
** File description:
** Source code
*/

#include "SFML/Graphics.h"
#include "distract/debug.h"
#include <stdio.h>

sfSprite *create_sprite(sfTexture *texture, sfIntRect *rect)
{
    sfSprite *sprite = sfSprite_create();

    if (sprite == NULL) {
        fprintf(stderr, "Sprite could not be initted");
        return (NULL);
    }
    if (texture != NULL)
        sfSprite_setTexture(sprite, texture, sfFalse);
    if (rect != NULL)
        sfSprite_setTextureRect(sprite, *rect);
    return (sprite);
}
