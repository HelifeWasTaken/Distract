# Distract

## The Entity System

### What is an Entity in Programming?

An entity is a single object in the game world.

This entity will be managed by the game engine trough the scene manager.

Do you remeber the scene paradigm?

- The Create method.
- The Draw method.
- The Update method.
- The Handle Event method.
- The Destroy method.

Thoses are not directly related to the scene but they are related to the entity.

Here is the struct of an entity:
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

typedef struct entity_info {
    struct entity_info *next;
    int type;
    bool (*create)(game_t *game, entity_t *entity);
    void (*draw)(game_t *game, entity_t *entity);
    void (*destroy)(game_t *game, entity_t *entity);
    void (*update)(game_t *game, entity_t *entity);
    bool (*handle_event)(game_t *game, entity_t *entity, sfEvent *event);
} entity_info_t;
```

What we need to pay attention to is the `entity_info_t` struct.

The `entity_info_t` struct is a struct that contains all the information about an entity.

It permits you to know the type of the entity, the creation, the draw, the update and the event handling.

It is a linked list and is also a register in the game engine.

When you create an entity, you need to register the `entity_info_t` struct in the game engine so you can use it in the game.

For example if you want to create an entity that is a player, you need to register the `entity_info_t` struct in the game engine.

```c
enum entity_type {
    ENTITY_PLAYER,
    ENTITY_ENEMY, // why not ?
    ENTITY_MAX // To dertmine the number of entity type
};

struct player {
	// foo
	struct entity *entity;
};

bool player_create(game_t *game, entity_t *entity)
{
    struct player *player = malloc(sizeof(struct player));
    if (player == NULL) {
        fprintf(stderr, "Could not allocate memory for player\n");
        return false;
    }
    player->entity = entity;
    entity->instance = player;
    return true;
}

void player_draw(game_t *game, entity_t *entity)
{
    struct player *player = entity->instance;
    // foo
}

void player_destroy(game_t *game, entity_t *entity)
{
    struct player *player = entity->instance;
    free(player);
}

// The update and the handle event...
```

This would be a sample of an entity player in the game

So the entity_info_t struct would look like this:
```c
(struct entity_info) {
    .type = ENTITY_PLAYER,
    .create = player_create,
    .draw = player_draw,
    .destroy = player_destroy,
    .update = player_update,
    .handle_event = player_handle_event
};
```
But how to use it in a lifecycle ?

Considering a play_lifecycle function in your source code her init function would look like this:

```c
// Considering thoses in a header file
enum entity_type {
    ENTITY_PLAYER,
    ENTITY_ENEMY, // why not ?
    ENTITY_MAX // To dertmine the number of entity type
};

struct entity_generator {
    int count;
    enum entity_type type;
};

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// And this in your source code

static const struct entity_generator ENTITIES_GAME_GENERATOR[] = {
    {1, ENTITY_PLAYER},
    {50, ENTITY_ENEMY}
};

static const entity_info_t ENTITIES_GAME_INFO[] = {
    ENTITY(ENTITY_PLAYER,
        player_create, player_draw, player_destroy, player_update, player_handle_event),
    ENTITY(ENTITY_ENEMY,
        enemy_create, enemy_draw, enemy_destroy, enemy_update, enemy_handle_event)
};

bool register_game_entities(game_t *game)
{
    for (int i = 0; i < ARRAY_SIZE(ENTITIES_GAME_INFO); i++)
        if (register_entity(game, &ENTITIES_GAME_INFO[i]) == false)
            return false;
    return true;
}

bool create_game_entities(game_t *game)
{
    for (unsigned int i = 0; i < ARRAY_SIZE(ENTITIES_GAME_GENERATOR); i++)
        for (unsigned int j = 0; j < ENTITIES_GAME_GENERATOR[i].count; j++)
            if (create_entity(game, ENTITIES_INFOS_GAME[i].type) == false)
                return false;
    return true;
}

bool init_play_lifecycle(game_t *game)
{
    return register_game_entities(game) && create_game_entities(game);
}
```

So the `ENTITIES_GAME_INFO` array contains all the entity_info_t struct about each entity type.
Then the `ENTITIES_GAME_GENERATOR` array contains all the id and number of struct about each entity type.

As you see you need to register each entity_info_t struct in the game engine otherwise you will get an error saying that the entity is not registered.

You also cannot register twice the same entity_info_t struct.

### How to interact with my entities ?

Considering that you have the init_play_lifecycle function in source code how would you use your entities ???

Well it's nearly automatic.

Here is a sample:
```c
int play_lifecycle(game_t *game)
{
    if (init_play_lifecycle(game) == false)
        return -1;
    while (is_distract_scene_updated(game)) {
        while (sfRenderWindow_pollEvent(game->window, &game->event)) {
            if (event.type == sfEvtClosed))
                sfRenderWindow_close(game->window);
            else
                transmit_event_to_scene(game, &event);
        }
        update_scene(game);
        draw_scene(game);
        sfRenderWindow_display(game->window);
        sfRenderWindow_clear(game->window, sfBlack);
    }
    destroy_scene(game, true);
    return 0;
}

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

And now you can you any number of entities in your game as long as you have registered them in the game engine.

### Entities can be anything

Entities can be used to launch back end tasks (so variables such as position are useless but update are still automatic)

There has been one time where I used a entity to parse a json file and create a new entity for each object in the json file.

Thoses could be done with jobs (that will be seen in future) to be asynchrone.

### How to make entities connect to each other ?

If you want to make entities communicate you must know two things:
- The entity must be created in order
- Interdependencies between entities must be avoided

At the create of the entity you can get a pointer to the entity that will be created before you like this:
```c
// Let's say you have a player and a map and you want to make the player check on the map if there is a colision.

struct player {
    // ...
    const struct map *map;
    entity_t *entity;
};

bool player_create(game_t *game, entity_t *entity)
{
    struct player *player = malloc(sizeof(struct player));
    if (player == NULL) {
        fprintf(stderr, "Error: cannot allocate memory for player\n");
        return false;
    }
    player->map = get_instance(game, ENTITY_MAP);
    if (player->map == NULL) {
        fprintf(stderr, "Error: cannot find map\n");
        free(player);
        return false;
    }
    entity->instance = player;
    player->entity = entity;
    return true;
}
```

You can notice that we uses get_instance to get the map and not get_entity.

It is because get_entity returns a pointer to the entity and not the instance.

So it would need to be done like this if we uses get_entity:

```c
bool player_create(game_t *game, entity_t *entity)
{
    struct player *player = malloc(sizeof(struct player));
    entity_t *entity = NULL;

    if (player == NULL) {
        fprintf(stderr, "Error: cannot allocate memory for player\n");
        return false;
    }
    entity = get_entity(game, ENTITY_MAP);
    if (entity == NULL) {
        fprintf(stderr, "Error: cannot find map\n");
        free(player);
        return false;
    }
    if (entity->instance == NULL) {
    	fprintf(stderr, "Error: Found map but instance is NULL\n");
	free(player);
	return false;
    }
    player->map = entity->instance;
    entity->instance = player;
    player->entity = entity;
    return true;
}
```

### I need to create my entity before the others how to connect them after the init ?

If you have an entity A that needs to stock a pointer to an entity B but A must be created before B you can do this: (this should not be done too often as it can lead to messy code)
```c
bool entityAcreate(game_t *game, entity_t *entity)
{
    // foo
}

void entityAupdate(game_t *game, entity_t *entity)
{
    entityA_t *entity = entity->instance;

    if (entity->entityB_pointer == NULL) {
        entity->entityB_pointer = get_instance(game, ENTITY_B);
        if (entity->entityB_pointer == NULL) {
            fprintf(stderr, "Error: cannot find entity B\n");
            // abort(); (maybe)
        }
    }
    // foo ...
}
```
This way you can get a reference to the entity B after creating both A and B

But as said interdependencies should be avoided as much as possible

### I got an entity but I have multiples ones how can I get the next one ?

```c
entity_t *get_next_entity_of_type(entity_t *entity, int type);
```
Will return you the next entity of the type specified starting from the entity passed as parameter.

### I want my entities to be sorted by a specific attribute is there a way to do that ?

The Z order is the default attribute to sort entities.
Set it when you create your entity: `your_entity->z = any_i32_value;`

The function to sort entities is:
```c
void sort_entities(game_t *game);
```

### I need to differenciate gui and non gui entities

A draw_on_gui variable can be added to your entity. (we will see it later with windows and graphics)

### I want to access to have more variables in the prototype of my entity

Don't.
Use configuration files instead.

If you really think a configuration file is overkill at the moment you can store it temporarily in the game struct with `game->stockage`.
