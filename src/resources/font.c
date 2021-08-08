/*
** EPITECH PROJECT, 2020
** font
** File description:
** Source code
*/

#include "distract/game.h"
#include "distract/debug.h"
#include "distract/resources.h"
#include "SFML/Graphics.h"
#include "stdio.h"
#include "stdarg.h"

sfFont *create_font(game_t *game, char *filepath)
{
    distract_resource_t *distract_resource = get_distract_resource(game, filepath);

    if (distract_resource == NULL) {
        distract_resource = create_distract_resource(game, filepath, DR_FONT);
        if (distract_resource == NULL) {
            fprintf(stderr, "Resource could not be created");
            return (NULL);
        }
        distract_resource->font = sfFont_createFromFile(filepath);
        if (distract_resource->font == NULL) {
            fprintf(stderr, "Resource could not be created");
        }
    }
    return (distract_resource->font);
}

void destroy_fonts(int count, ...)
{
    va_list ap;
    sfFont *font;

    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        font = va_arg(ap, sfFont *);
        SAFE_RESOURCE_DESTROY(sfFont_destroy, font);
    }
    va_end(ap);
}
