# Distract

## Scenes

### Basics

A scene in a game is also called a state.

A state can be the game menu, the game play screen, the game over screen, etc.

It is a way to manage the flow of the game.

Every state has a set of rules that define how the game behaves.

That are principally defniend by the game engine.

The ones that are most important are:
	- The Create method.
	- The Draw method.
	- The Update method.
	- The Handle Event method.
	- The Destroy method.

Thoses are going to be seen more in depth in the Entities chapter.

### A sample of how is a scene called

```c
enum distract_scene_id {
	PLAY_SCENE,
};

int play_lifecycle(game_t *game)
{
    // foo
}
// You need to register the corresponding distract_scene to the registry.
int main(void)
{
    game_t *game = create_game();

    if (game == NULL)
        return;
    if (register_distract_scene(game, PLAY_SCENE, &play_lifecycle) == false) {
        destroy_game(game);
        return 1;
    }
    game->mode = MODE(1280, 720, 32); // 1280x720, with 32 bit color depth
    game->window = create_standard_window(game->mode, "My Game");
    set_pending_distract_scene(game, PLAY_SCENE);
    do {
        code = load_pending_distract_scene(game);
        if (code != 0) {
            destroy_game(game);
            exit(code);
        }
    } while (has_pending_distract_scene(game));
    destroy_game(game);
    return 0;
}
```

This piece of code is a bit more complex than the previous one.
I will try to explain it step by step.

    - The first thing to notice is that we have a new scene.
    - The scene is registered in the registry.
    - The scene is created.
    - The scene is set as the pending scene.
    - The game loop is entered.
    - The pending scene is loaded.

You need to know that a scene can chose to change of scene by calling switch_to_distract_scene and chosing the id of the new scene.

So the current scene is destroyed and the new one is created.
```c
void switch_to_distract_scene(game_t *game, int id);
```

Every scene must be registered in the registry otherwise it will not be created and the game might crash.

The has_pending_distract_scene function is used to check if the game consider loading a new scene otherwise it will leave.

The loop here considers that if scene has returned a non zero value, a problem has occurred and the game is terminated.

### Switch from scenes to scenes

A typical **basic** scene will be something like this:
```c
enum distract_scene_id {
    PLAY_SCENE,
	MENU_SCENE,
}

int menu_lifecycle(game_t *game)
{
    // Runs a basic window prompt screen
    // ...
    if (user_hit_button_play_for_example()) {
        switch_to_distract_scene(game, PLAY_SCENE);
        return 0; // leave_function
    }
}

int play_lifecycle(game_t *game)
{
    // User can play and whatever
    return 0;
}

int main(void)
{
    game_t *game = create_game();

    if (game == NULL)
        return;
    if (register_distract_scene(game, PLAY_SCENE, &play_lifecycle) == false ||
        register_distract_scene(game, MENU_SCENE, &menu_lifecycle) == false) {
        destroy_game(game);
        return 1;
    }
    game->mode = MODE(1280, 720, 32); // 1280x720, with 32 bit color depth
    game->window = create_standard_window(game->mode, "My Game");
    set_pending_distract_scene(game, MENU_SCENE);
    do {
        code = load_pending_distract_scene(game);
        if (code != 0) {
            destroy_game(game);
            exit(code);
        }
    } while (has_pending_distract_scene(game));
    destroy_game(game);
    return 0;
}
```
This is a basic example of a scene.
The menu_lifecycle function is called at the beginning of the scene.
Then if the user hits the play button, the scene is changed to the play scene.