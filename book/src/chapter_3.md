# Distract

## Draw your first image

You could open your first window but it was not very useful.

Now it is time to draw something.

```c
#include "distract/game.h"
#include "distract/window.h"
#include "distract/graphics.h"

int main(void)
{
	struct game *game = create_game();
    sfSprite *sprite = NULL;
    sfTexture *texture = NULL;

	if (game == NULL)
		return 1;
	game->mode = mode(1280, 720, 60);
	game->window = create_standard_window(game->mode, "my first window! :d");
    texture = create_texture(game, "image.png");
    sprite = create_sprite(texture, NULL);
    if (window == NULL || texture == NULL || sprite == NULL) {
        if (sprite != NULL)
            sfSprite_destroy(sprite);
        destroy_game(game);
        return 1;
    }
	while (is_distract_scene_updated(game)) {
		while (sfRenderWindow_pollevent(game->window, &game->event)) {
			if (event.type == sfEvtclosed) {
				sfRenderWindow_close(game->window);
			}
		}
        sfRenderWindow_clear(game->window, sfBlack);
        sfRenderWindow_draw(game->window, sprite, NULL);
        sfRenderWindow_display(game->window);
	}
    sfSprite_destroy(sprite);
    destroy_game(game);
    return 0;
}
```

Now we can start initializing some texture for our sprite.
A texture is a image that can be used to draw a sprite.
The create_texture function will return a pointer to a sfTexture object.
The second arguement is used to indicate the size of the texture. If we specified NULL the engine will use the size of the image.

The first thing to notice is that we need to check if the texture and the sprite is valid.
If for example the image could not be loaded, the engine will print a message on stderr and return a null pointer.

Why is important to check if the sprite is valid?
If for example we try to draw a sprite that does not exist, the game will instantly crash.

The engine will not care if the texture is valid or not.
Except if you use the CSFML API, the engine will check if the texture is valid.

Even though a error message will be printed, but the engine will not crash.

Then we can notice that we are using the `sfRenderWindow` class to draw the sprite.
The first one is the clear that liteally clears the screen.
The second one is the draw that actually draws the sprite.
The thrid one is display and this is the one that shows the sprite to the user.
Pretty simple right?

I would recommend you to check the `sfRenderWindow` class documentation.

An important thing to notice is that draw and display are not the same.
Draw is a function that will put the sprite in the window.
Display is a function that will draw the sprite to the user that you put in the window.

Also do not forget to destroy the sprite at the end.

You can notice that we did not destroy the texture at the end of the loop.
It is because the destroy_game function will destroy the texture by itself as long as you use the wrappers of Distract.
Creating a sprite with sfTexture_create will need you to destroy it manually.
Otherwise you should not destroy a texture created with create_texture or any resource type (see the distract_resource_t structure). But with the destroy_resource function. (You might not use this function but it is still important to know that it exists.)

All the resources such as the texture, the music, sound buffers, sound, font, and vertex arrays are destroyed automatically by the `game manager` at the end of the scene.

You might say actually it is not that simple.
Or it might take a lot of messy code to draw a sprite.
But the thing will start becoming interestring as soon as you will get to entities section.
Keep going!