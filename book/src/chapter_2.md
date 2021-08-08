# Distract

## A first step with distract

Create your first window:

```c
#include "distract/game.h"
#include "distract/window.h"

int main(void)
{
	struct game *game = create_game();

	if (game == NULL)
		return 1;
	game->mode = mode(1280, 720, 60);
	game->window = create_standard_window(game->mode, "my first window! :d");
	if (game->window == NULL) {
		destroy_game(game);
		return 1;
	}
	while (is_distract_scene_updated(game)) {
		while (sfRenderWindow_pollEvent(game->window, &game->event)) {
			if (event.type == sfEvtClosed) {
				sfRenderWindow_close(game->window);
			}
		}
	}
    destroy_game(game);
    return 0;
}
```

Here the game is created, the window is created and you have now a blank window!

Not that impressive yes I know, but you can do more with it!

You will see further that game has a lot of secret variables, but you can also use them.

For now let's try to understand this code.

The `create_game()` function will create a game and return a pointer to it.

As the memory is allocated on the heap we have to check if the pointer is not NULL.

MODE is a macro permitting to initailize is a struct that contains the resolution, the refresh rate and the bits per pixel.
The parameters are:
 - `int width`: the width of the window
 - `int height`: the height of the window
 - `int refresh_rate`: the refresh rate of the window

Then you can create a window with the `create_standard_window()` function.

You also have to check if the pointer is not NULL.
And of course to destroy the game.

Then the while loop will be entered until the scene is updated.

This loop is kind of an alias to the `sfRenderWindow_isOpen()` function but will also check some internal stuff of Distract it self.

Then the `sfRenderWindow_pollEvent()` function will be called to get event/input from the window.
If the event is a close event then the window will be closed.
And finally the destroy_game() function will be called to destroy the game.
This destroy function will also destroy the window if it is not already destroyed. (and a lot more to come)