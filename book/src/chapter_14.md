# Distract

## The FrameBuffer

A framebuffer is a special kind of memory that can be written to and read from.
It is generally used to display graphics.

The Distract API provides a framebuffer object that can be used to display and a put_pixel function that can be used to write to the framebuffer.

Header guard of the `framebuffer.h`:
```c
#include "SFML/Graphics.h"

typedef struct framebuffer {
    unsigned int width;
    unsigned int height;
    sfUint8 *pixels;
} framebuffer_t;

///
/// Create a framebuffer, a drawable area of pixels.
///
framebuffer_t *framebuffer_create(int width, int height);

///
/// Clear the framebuffer
///
void framebuffer_clear(framebuffer_t *framebuffer);

///
/// Destroy the framebuffer.
///
void framebuffer_destroy(framebuffer_t *framebuffer);

///
/// Put a pixel in the framebuffer.
///
void put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y, sfColor color);
```

You can use it like this:
```c
#include <distract/framebuffer.h>

int main(void)
{
    game_t *game = create_game();
    framebuffer_t *framebuffer = framebuffer_create(1920, 1080);

    if (framebuffer == NULL || game == NULL)
        return 1;
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_create(1920, 1080);
    game->mode = MODE(1280, 720, 60);
    game->window = create_standard_window(game->mode, "Window Name");
    if (game->window == NULL) {
        framebuffer_destroy(framebuffer);
        destroy_game(game);
        sfSprite_destroy(sprite);
        sfTexture_destroy(texture);
        return 1;
    }
    framebuffer_clear(framebuffer);
    put_pixel(framebuffer, 100, 100, sfRed);
    put_pixel(framebuffer, 200, 200, sfBlue);
    put_pixel(framebuffer, 300, 300, sfGreen);
    put_pixel(framebuffer, 400, 400, sfYellow);
    put_pixel(framebuffer, 500, 500, sfMagenta);
    while (is_distract_scene_updated(game)) {
        sfTexture_updateFromPixels(texture, framebuffer->pixels, framebuffer->width, framebuffer->height, 0, 0);
        sfSprite_setTexture(sprite, texture);
        while (sfRenderWindow_pollEvent(game->window, &game->event)) {
            if (game->event.type == sfEvtClose) {
                sfRenderWindow_close(game->window);
                break;
            }
        }
        sfRenderWindow_drawSprite(game->window, sprite, NULL);
        sfRenderWindow_display(game->window);
        sfRenderWindow_clear(game->window);
    }
    game_destroy(game);
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    framebuffer_destroy(framebuffer);
    return 0;
}
```