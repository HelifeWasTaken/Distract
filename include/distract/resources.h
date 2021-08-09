/*
** EPITECH PROJECT, 2020
** distract_resources
** File description:
** Source code
*/

#ifndef DISTRACT_RESOURCES_H
#define DISTRACT_RESOURCES_H
#include "SFML/Graphics.h"
#include "SFML/Audio.h"
#include "distract/def.h"
#include "distract/game.h"
#include "distract/hashmap.h"

///
/// Type of distract_resource in registry
///
enum distract_resource_type {
    DR_TEXTURE,
    DR_MUSIC,
    DR_SOUND_BUFFER,
    DR_SOUND,
    DR_FONT,
    DR_VERTEX
};

///
/// Resource in the distract_resources registry
///
typedef struct distract_resource {
    enum distract_resource_type type;
    char *path;
    union {
        sfTexture *texture;
        sfMusic *distract_music;
        sfSoundBuffer *distract_sound_buffer;
        sfSound *distract_sound;
        sfFont *font;
    };
} distract_resource_t;

#define GENERIC_RESOURCE_DESTROY(distract_resource) \
    _Generic((distract_resource), \
        sfTexture *: sfTexture_destroy, \
        sfSound *: sfSound_destroy, \
        sfSoundBuffer *: sfSoundBuffer_destroy, \
        sfMusic *: sfMusic_destroy, \
        sfFont *: sfFont_destroy, \

#define SAFE_RESOURCE_DESTROY(fun, res) \
    do { \
        if (res) \
            fun(res); \
    } while (0)

///
/// Create a distract_resource of type from the file.
///
/// You would rather use other methods like `create_texture`, `create_font`,
/// `create_distract_sound` instead
///
distract_resource_t *create_distract_resource(game_t *game, char *file, enum distract_resource_type type);

///
/// Destroy the specified distract_resource, freeing it.
///
void destroy_distract_resource(game_t *game, distract_resource_t *distract_resource);

///
/// Get distract_resource by name.
///
distract_resource_t *get_distract_resource(game_t *game, char *file);

///
/// Destroy distract_resource by name, freeing it.
///
void destroy_distract_resource_by_name(game_t *game, char *file);

///
/// Create and register a texture, with a size of rect.
/// If texture is already in memory, will return the existing instance.
///
sfTexture *create_texture(game_t *game, char *file, sfIntRect *rect);

///
/// Destroy textures.
/// count is the number of textures.
/// Other arguments are sfTexture*
///
void destroy_textures(int count, ...);

///
/// Create and register a font.
/// If font is already in memory, will return the existing instance.
///
sfFont *create_font(game_t *game, char *filepath);

///
/// Destroy fonts by instances.
/// count is the number of items.
/// Other arguments are sfFont*
///
void destroy_fonts(int count, ...);

///
/// Create and register a distract_sound (and the appropriate distract_soundbuffer automatically).
/// If distract_sound is already in memory, will return the existing instance.
///
sfSound *create_distract_sound(game_t *game, char *filepath);

///
/// Create and register a distract_music.
/// If distract_music is already in memory, will return the existing instance.
///
sfMusic *create_distract_music(game_t *game, char *filepath);

#define DESTROY_TEXTURES(...) \
    destroy_textures(ARGS_COUNT(# __VA_ARGS__), ## __VA_ARGS__)

#define DESTROY_FONTS(...) \
    destroy_fonts(ARGS_COUNT(# __VA_ARGS__), ## __VA_ARGS__)

#endif //DISTRACT_RESOURCES_H
