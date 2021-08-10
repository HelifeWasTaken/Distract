# Distract

## Authors:
- Alexis Cheron (Original Author) -> [Norech Github's](https://github.com/norech)
- Mattis Dalleau (Resources Handler, Input, Memory Management (Leak Check), Bit of Entities, The Book) [Me](https://github.com/Heliferepo/Distract)

This is a rework mostly done while an RPG project was made Alexis Cheron came with his library and I helped him doing the things listed above...

## How to use

### Create a game with a window

```c
    #include "distract/game.h"
    #include "distract/window.h"

    game_t *game = create_game();

    if (game == NULL)
        return;
    game->mode = MODE(1280, 720, 32); // 1280x720, with 32 bit color depth
    game->window = create_standard_window(game->mode, "My Game");

    // Set the distract_scene to load first
    set_pending_distract_scene(game, MENU_SCENE);

    // Will loop while there are distract_scenes to load, the global distract_scene loop
    do {
        code = load_pending_distract_scene(game);
        if (code != 0) // the exit code is non-zero, so we exit
            exit(code);
    } while (has_pending_distract_scene(game));

    destroy_game(game);
```

### Create a new distract_scene

Each distract_scene must have a lifecycle.

A lifecycle is a function that will be called each time the distract_scene is loaded.

The returned code will be propagated, and usually correspond to the exit code.

```c
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/resources.h"

// The lifecycle of the play distract_scene
int play_lifecycle(game_t *game)
{
    sfEvent event;

    // Until the distract_scene is closed
    while (is_distract_scene_updated(game)) {

        // poll events
        while (sfRenderWindow_pollEvent(game->window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(game->window);
            } else {
                // Send events to the entities
                transmit_event_to_distract_scene(game, &event);
            }
        }

        // update each entities of the sprite
        update_distract_scene(game);

        // clear the distract_scene
        sfRenderWindow_clear(game->window, sfWhite);

        // draw each entities of the sprite
        draw_distract_scene(game);

        // display the window
        sfRenderWindow_display(game->window);
    }

    // destroy the distract_scene and the distract_resources
    destroy_distract_scene(game, true);

    return (0);
}
```

And we add it to our project header file:

```c
    // An enum with every distract_scenes
    enum distract_scene_id {
        PLAY_SCENE,
    };

    int play_lifecycle(game_t *game);
```

You need to register the corresponding distract_scene to the registry.

```c
    game_t *game = create_game();

    // ...

    register_distract_scene(game, PLAY_SCENE, &play_lifecycle);

    // ...

    // game loop
```


### Create an entity

An entity is a single compartimentarized unit with data and behaviour.

You first need to describe your entity and data structure.

```c
    #include "distract/entity.h"

    // An enum with every entities
    enum entity_id {
        CUSTOMENTITY,
    };

    // The structure defining the entity
    typedef customentity {
        entity_t *entity;
        sfSprite *sprite;
    } customentity_t;

    // Below are several "hook" functions for the entity
    // All of them are optional

    void create_customentity(game_t *game, entity_t *entity);
    void destroy_customentity(game_t *game, entity_t *entity);
    void update_player(game_t *game, entity_t *entity);
    void draw_player(game_t *game, entity_t *entity);
```

Once you got your data structure, you can implement the functions:

```c
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/resources.h"
#include "distract/graphics.h"
#include "stdlib.h"
#include "<yourproject>/entities.h"

// will be called when the entity is created
// if the `instance` property is NULL, the entity will not be created
void create_customentity(game_t *game, entity_t *entity)
{
    // allocate space for customentity_t
    customentity_t *customentity = malloc(sizeof(customentity_t));

    // if allocation fails
    if (customentity == NULL)
        return;

    // texture bounds
    sfIntRect rect = IRECT(0, 0, 300, 200);

    // create or fetch a texture in the registry and return it
    sfTexture *texture = create_texture(game, "assets/sprite.png", &rect);

    // link customentity->entity to entity for easier access
    customentity->entity = entity;

    // create a sprite from the texture
    customentity->sprite = create_sprite(texture, NULL);

    // attach our customentity structure to the entity
    entity->instance = customentity;
}

// will be called when the entity is destroyed
void destroy_customentity(game_t *game, entity_t *entity)
{
    customentity_t *customentity = entity->instance;

    sfSprite_destroy(customentity->sprite);
    free(customentity);
}

// will be called when the entity is updated
void update_player(game_t *game, entity_t *entity)
{
    customentity_t *customentity = entity->instance;

    // set the position of the sprite to the position of the entity
    sfSprite_setPosition(customentity->sprite, entity->pos);
}

// will be called when the entity is drawn
void draw_player(game_t *game, entity_t *entity)
{
    customentity_t *customentity = entity->instance;

    // draw the sprite
    sfRenderWindow_drawSprite(game->window, customentity->sprite, NULL);
}


// will be called when an event is transmitted to the entity
bool handle_player_events(game_t *game, entity_t *entity, sfEvent *event)
{
    customentity_t *customentity = entity->instance;

    sfIntRect *bounds = sfSprite_getGlobalBounds(customentity->sprite);

    if (event->type == sfEvtMouseButtonPressed) {

        sfMouseButtonEvent click = event->mouseButton;

        if (sfFloatRect_contains(&bounds, move.x, move.y) && click.button == sfMouseLeft) {
            printf("the player sprite has been clicked!");

            // the event is succesfully caught
            return (true);
        }
    }

    // the event has not been caught
    return (false);
}
```

You then need to register the entity to the entities' registry:

```c
    game_t *game = create_game();

    // ...

    register_entity(game, &ENTITY(
        CUSTOMENTITY,                 // the entity id
        &create_customentity,         // the function called when created
        &draw_customentity,           // the function called when drawn
        &destroy_customentity,        // the function called when destroyed
        &update_customentity,         // the function called when updated
        &handle_customentity_events   // the function called when events are called
    ));

    // ...

    // game loop
```

### Parallelize the entities logic

Sometimes, you may have **a lot** of entities or several entities with slow
logic. All these entities will execute their update logic one by one,
each one before the other, and their execution time will stack up.
If you have a very slow update routines, it can take a lot of time,
especially if you have many entities in your distract_scene.

You may want to parallelize the entities logic on entities that you suspect
may need to be ran on another thread using the power of multithreading.

To use multithreading and run the entity update logic on another thread,
you need to go in your create function hook and set the
`entity->use_multithreading` property to `true`.

```c
void create_customentity(game_t *game, entity_t *entity)
{
    //...

    entity->use_multithreading = true;

    //...
}

void update_customentity(game_t *game, entity_t *entity)
{
    customentity_t *customentity = entity->instance;

    // ... the slow code goes here
}
```

### Place an entity in a distract_scene

#### Create a simple entity

```c
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/resources.h"

// The lifecycle of the play distract_scene
int play_lifecycle(game_t *game)
{
    sfEvent event;

    //...

    // Create an entity of type CUSTOMENTITY
    // The events/destroy will be automatically hooked
    create_entity(game, CUSTOMENTITY);

    // ...

    // Until the distract_scene is closed
    while (is_distract_scene_updated(game)) {
        // ...
    }

    destroy_distract_scene(game, true); // the entity will be destroyed with the distract_scene
}
```

#### Create an entity and set one of its properties

```c
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/resources.h"

// The lifecycle of the play distract_scene
int play_lifecycle(game_t *game)
{
    sfEvent event;

    //...

    // create the entity and get its instance
    entity_t *entity = create_entity(game, CUSTOMENTITY);

    // If entity failed to be created, exit with error
    if (entity != NULL)
        return (84);

    // The instance is garanteed to be non-NULL at this point
    customentity_t *customentity = entity->instance;

    // will tint red the entity sprite
    sfSprite_setColor(customentity->sprite, sfRed);

    // ...

    // Until the distract_scene is closed
    while (is_distract_scene_updated(game)) {
        // ...
    }

    destroy_distract_scene(game, true); // the entity will be destroyed with the distract_scene
}
```

### Get an existing entity

The `GET_ENTITY` macro will get the first sprite matching the entity type.

```c
customentity_t *customentity = GET_ENTITY(game, CUSTOMENTITY)->instance;

// ...
```

> WARNING: `GET_ENTITY(game, type)` may return `NULL` if no entity of the type exist!

### Get every entity of type

In the case where you have several entities matching the type,
you can get the entities with the `FOREACH_ENTITY_OF_TYPE(entity_type, entities, entity)` macro.

```c
FOREACH_ENTITY_OF_TYPE(CUSTOMENTITY, game->distract_scene->entities, entity) {
    customentity_t *customentity = entity->instance;

    // ...
}
```

### Create distract_job

You may want to perform code outside the game loop while not blocking the
game loop.


```c
#include "stdio.h"
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/resources.h"
#include "distract/job.h"

// Note: this function will be executed asynchronously from another thread
void my_distract_job(distract_job_t *distract_job)
{
    // sleep some time
    sfSleep((sfTime) { 1000000 });

    printf("I'm in the thread!");
}

// The lifecycle of the play distract_scene
int play_lifecycle(game_t *game)
{
    // create the distract_job
    distract_job_t *distract_job = create_distract_job(&my_distract_job, NULL)

    if (distract_job == NULL)
        return (84);

    // start the distract_job
    start_distract_job(distract_job);

    // Until the distract_scene is closed
    while (is_distract_scene_updated(game)) {
        // ...
    }

    // destroy our distract_job
    destroy_distract_job(distract_job);

    // ...
}
```

### Send messages inside and outside a distract_job

You may want to communicate with your distract_job to get status, update, or trigger events.

```c
#include "stdio.h"
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/resources.h"
#include "distract/job.h"

enum message_type {
    MYJOB_MESSAGE
};

// Note: this function will be executed asynchronously in another thread
void my_distract_job(distract_job_t *distract_job)
{
    // send a message to the main game loop
    // note that `send_distract_job_message` take a `void *` as third argument
    send_distract_job_message(distract_job, MYJOB_MESSAGE, "One!");

    // we can wait, it does not impact our game loop
    sfSleep((sfTime) { 10000 });

    send_distract_job_message(distract_job, MYJOB_MESSAGE, "Two!");

    sfSleep((sfTime) { 10000 });

    send_distract_job_message(distract_job, MYJOB_MESSAGE, "Three!");

}

// The lifecycle of the play distract_scene
int play_lifecycle(game_t *game)
{
    // create the distract_job
    distract_job_t *distract_job = create_distract_job(&my_distract_job, NULL)

    if (distract_job == NULL)
        return (84);

    start_distract_job(distract_job);

    // Until the distract_scene is closed
    while (is_distract_scene_updated(game)) {

        // receive messages from the distract_job
        // note: `poll_distract_job_message` returns a `void *`
        char *msg;
        while ((msg = poll_distract_job_message(distract_job, MYJOB_MESSAGE)) != NULL) {
            printf("Game loop is receiving: %s\n", msg);
        }

        // ...
    }

    destroy_distract_job(distract_job);
    destroy_distract_scene(game, true); // the entity will be destroyed with the distract_scene
    // ...
}
```

```
Game loop is receiving: One!
Game loop is receiving: Two!
Game loop is receiving: Three!
```

A more complex variant:

```c
#include "stdio.h"
#include "distract/game.h"
#include "distract/entity.h"
#include "distract/resources.h"
#include "distract/job.h"

enum message_type {
    MYJOB_MESSAGE,
    GAME_MESSAGE
};

// Note: this function will be executed asynchronously in another thread
void my_distract_job(distract_job_t *distract_job)
{
    // send a message to the main game loop
    send_distract_job_message(distract_job, MYJOB_MESSAGE, "Hello!");

    // we can wait, it does not impact our game loop
    sfSleep((sfTime) { 100000 });

    // this distract_job will never end, but since its in another thread,
    // it will not block our game loop
    while (true) {

        // check if we've got messages
        char *msg;
        while ((msg = poll_distract_job_message(distract_job, GAME_MESSAGE)) != NULL) {
            printf("Job is receiving: %s\n", msg);
        }

        // sleep some time
        sfSleep((sfTime) { 10000 });

    }
}

// The lifecycle of the play distract_scene
int play_lifecycle(game_t *game)
{
    // create the distract_job
    distract_job_t *distract_job = create_distract_job(&my_distract_job, NULL)

    if (distract_job == NULL)
        return (84);

    start_distract_job(distract_job);

    // Until the distract_scene is closed
    while (is_distract_scene_updated(game)) {

        // receive messages from the distract_job
        char *msg;
        while ((msg = poll_distract_job_message(distract_job, MYJOB_MESSAGE)) != NULL) {
            printf("Game loop is receiving: %s\n", msg);
        }

        // ...
    }

    destroy_distract_job(distract_job);
    destroy_distract_scene(game, true); // the entity will be destroyed with the distract_scene
    // ...
}
```

### Wait that a distract_job end

```c
enum message_type {
    SOME_MESSAGE
};

void my_distract_job(distract_job_t *distract_job)
{
    // our game loop will wait that the sleep is completed
    sfSleep((sfTime) { 500000 });

    send_distract_job_message(distract_job, SOME_MESSAGE, "hello");
}

// some entrypoint function that we will call somewhere
void some_function()
{
    distract_job_t *distract_job = create_distract_job(&my_distract_job, NULL);

    start_distract_job(distract_job);

    // it will stop the execution until the distract_job is completed
    wait_distract_job(distract_job);

    // we can still get the unread messages from the distract_job
    // even if at this point the distract_job is stopped
    char *msg;
    while ((msg = poll_distract_job_message(distract_job, SOME_MESSAGE)) != NULL) {
        printf("The message was %s\n", msg);
    }

    destroy_distract_job(distract_job);
}
```

A more complex variant of what we can do:

```c
enum message_type {
    SOME_MESSAGE,
    WAIT_FODR_JOB
};

void my_distract_job(distract_job_t *distract_job)
{
    sfSleep((sfTime) { 200000 });

    // this message will call the wait_distract_job
    // in the other thread, as defined below
    send_distract_job_message(distract_job, WAIT_FODR_JOB, "");

    // our game loop will be stuck by this wait, since at this point,
    // wait_distract_job was called on the other thread
    sfSleep((sfTime) { 500000 });

    send_distract_job_message(distract_job, SOME_MESSAGE, "hello");
}

int play_lifecycle(game_t *game)
{
    distract_job_t *distract_job = create_distract_job(&my_distract_job, NULL);

    start_distract_job(distract_job);

    while (is_distract_scene_updated(game)) {

        // ... you can do stuff while it does not wait the distract_job

        // an example usage would be to wait for a message triggering the
        // synchronization
        if (poll_distract_job_message(distract_job, WAIT_FODR_JOB) != NULL) {

            // wait that the distract_job is completed
            wait_distract_job(distract_job);

            // we can still get the unread messages from the distract_job
            // even if at this point the distract_job is stopped
            char *msg;
            while ((msg = poll_distract_job_message(distract_job, SOME_MESSAGE)) != NULL) {
                printf("The message was %s\n", msg);
            }

            break; // exit the game loop
        }

    }

    destroy_distract_job(distract_job);
    destroy_distract_scene(game, true); // the entity will be destroyed with the distract_scene
    // ...
}
```
