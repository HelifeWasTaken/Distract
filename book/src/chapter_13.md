# Distract

## Multi-threading

If you don't know what multi-threading is, you should read [this](http://en.wikipedia.org/wiki/Multithreading).
If you don't know what thread is, you should read [this](http://en.wikipedia.org/wiki/Thread_(computing)).
If you don't know what mutex is, you should read [this](http://en.wikipedia.org/wiki/Mutual_exclusion).

### Create a Distract Job

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

### How to send messages inside and outside a distract_job

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
