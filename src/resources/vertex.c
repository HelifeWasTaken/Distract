/*
** EPITECH PROJECT, 2021
** vertex
** File description:
** vertex
*/

#include "distract/resources.h"
#include "distract/debug.h"
#include <stdio.h>

sfVertexArray *create_vertex(game_t *game, char *filepath)
{
    distract_resource_t *distract_resource = get_distract_resource(game, filepath);

    if (distract_resource == NULL) {
        distract_resource = create_distract_resource(game, filepath, DR_VERTEX);
        if (distract_resource == NULL)
            return (NULL);
        if ((distract_resource->vao = sfVertexArray_create()) == NULL)
            fprintf(stderr, "Failed to init vao");
    }
    return (distract_resource->vao);
}
