/*
** EPITECH PROJECT, 2020
** texture
** File description:
** Source code
*/

#include "distract/game.h"
#include "distract/debug.h"
#include "distract/resources.h"
#include "SFML/Graphics.h"
#include "stdio.h"
#include "stdarg.h"

sfTexture *create_texture(game_t *game, char *filepath, sfIntRect *rect)
{
    distract_resource_t *distract_resource = get_distract_resource(game, filepath);

    if (distract_resource == NULL) {
        distract_resource = create_distract_resource(game, filepath, DR_TEXTURE);
        if (distract_resource == NULL)
            return (NULL);
        if ((distract_resource->texture =
            sfTexture_createFromFile(filepath, rect)) == NULL)
            fprintf(stderr, "Failed to init texture");
    }
    return (distract_resource->texture);
}

void destroy_textures(int count, ...)
{
    va_list ap;
    sfTexture *texture;

    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        texture = va_arg(ap, sfTexture *);
        SAFE_RESOURCE_DESTROY(sfTexture_destroy, texture);
    }
    va_end(ap);
}
