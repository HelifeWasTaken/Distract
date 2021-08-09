# Distract

## Baby Graphics

This will be a little introduction to Graphics in Distract.

Please make sure that you know how the resources are managed before digging to far into this subject.

### The sfView

The sfView is the main container for the application. It is the first thing that is rendered when the application is loaded.

When a sfView is created, it is given a sfContext. This is the main object that is used to access the application's resources.

Generally for a game two sfView will be used (one for the game and one for the GUI).

In the game struct we can see two sfViews.
```c
typedef struct game {
    sfRenderWindow *window;
    sfRenderStates renderer;
    struct distract_scene_info *distract_scenes;
    struct entity_info *entities;
    struct distract_scene *distract_scene;
    struct distract_sound_emitter *distract_sound;
    sfVideoMode mode;
    sfBool is_paused;
    sfView *gui_view;
    sfView *view;
    struct input input;
    bool is_closing;
    void *stockage;
} game_t;
```

Make sure to set well your Game View with the `set_game_view` function.
```c
void set_game_view(game_t *game, sfView *view);
```

To chose beween the game view and the GUI view with your entities you can use the `draw_on_gui` variable

```c
typedef struct entity {
    struct entity *next;
    struct entity *prev;
    struct entity_info *info;
    sfVector2f pos;
    int type;
    int z;
    void *instance;
    bool use_multithreading;
    struct thread_info *threadinfo;
    bool draw_on_gui;
} entity_t;
```

### Text draw utilities

Here are some functions to help you draw pretty text.

```c
///
/// Align the bottom of the sfText to y_pos
///
sfText *align_text_bottom(sfText *text, int y_pos);

///
/// Align the right of the sfText to x_pos
///
sfText *align_text_right(sfText *text, int x_pos);

///
/// Align the sfText X axis at the center of start_x and end_x
///
sfText *center_text_x(sfText *text, int start_x, int end_x);

///
/// Align the sfText Y axis at the center of start_y and end_y
///
sfText *center_text_y(sfText *text, int start_y, int end_y);
```