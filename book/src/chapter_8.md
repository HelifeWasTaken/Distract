# Distract

## Input Handling

The Input Handling is a very important part of the game.

Some of the most important things to remember are:
```c
// The input is stored in the struct input_t.

typedef struct keyboard_input {
    bool is_being_pressed;
    bool is_pressed;
    bool is_being_released;
    bool was_pressed;
} keyboard_input_t;

typedef struct input {
    struct keyboard_input keys[sfKeyCount];
} input_t;
```

You can have a lot of informations about the state of the keyboard and has been made to avoid ghost press.

You can use the following macros to get the state of the keyboard:
```c

#define GET_INPUT_KEY(code) \
    get_input_key(&game->input, (code))

#define WAS_KEY_DOWN(code) \
    (get_input_key(&game->input, (code)).was_pressed)

#define WAS_KEY_UP(code) \
    (!get_input_key(&game->input, (code)).was_pressed)

#define IS_KEY_DOWN(code) \
    (get_input_key(&game->input, (code)).is_pressed)

#define IS_KEY_UP(code) \
    (!get_input_key(&game->input, (code)).is_pressed)

#define IS_KEY_PRESS_FRAME(code) \
    (get_input_key(&game->input, (code)).is_being_pressed)

#define IS_KEY_RELEASE_FRAME(code) \
    (get_input_key(&game->input, (code)).is_being_released)


```

For example a simple statement would be:
```c
if (IS_KEY_DOWN(sfKeySpace) == true) {
	// Do that
}
```

### How should this be implemented onto my entities ?

Considering a player entity:
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

typedef struct player {
    // foo
    entity_t *entity;
    bool up, down, left, right, space;
} player_t;

bool create_player(struct game *game, entity_t *entity)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL) {
        fprintf(stderr, "Failed to allocate memory for player\n");
        return false;
    }
    // foo
    player->entity = entity;
    entity->instance = player;
    return true;
}

void destroy_player(struct game *game, entity_t *entity)
{
    player_t *player = entity->instance;
    free(player);
    entity->instance = NULL;
}

void update_player(struct game *game, entity_t *entity)
{
    player_t *player = entity->instance;
    sfVector2f velocity = {0};

    if (player.up == true) {
        velocity.y -= 1;
    }
    if (player.down == true) {
        velocity.y += 1;
    }
    if (player.left == true) {
        velocity.x -= 1;
    }
    if (player.right == true) {
        velocity.x += 1;
    }
    if (player.space == true) {
        // Idk
    }
    velocity.x += entity->pos.x;
    velocity.y += entity->pos.y;

    // considering that the player has a sprite following the position of the Entity
    move_entity_towards(entity, velocity);
    // or just
    entity->pos = velocity;
}

bool handle_input_player(struct game *game, entity_t *entity, sfEvent *event)
{
    player_t *player = entity->instance;

    player.space = IS_KEY_DOWN(sfKeySpace);
    player.up = IS_KEY_DOWN(sfKeyUp);
    player.down = IS_KEY_DOWN(sfKeyDown);
    player.left = IS_KEY_DOWN(sfKeyLeft);
    player.right = IS_KEY_DOWN(sfKeyRight);
    return true;
}
```

To get the position of your mouse, you can use the following function:
```c
sfVector2f get_mouse_pos(sfRenderWindow *window, sfView *view);
```
This will return you the position of the mouse in the window relative to the view pixmap. (or Pixel size)

This is a very important function to use when you want to have a nice GUI on your game.