/*
** EPITECH PROJECT, 2020
** game
** File description:
** Source code
*/

#ifndef DISTRACT_GAME_H
#define DISTRACT_GAME_H
#include "SFML/Window.h"
#include "SFML/Graphics.h"
#include "distract/input.h"

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

#include "distract/scene.h"

///
/// Create a game instance.
///
game_t *create_game(void);

///
/// Destroy the game instance.
///
void destroy_game(game_t *game);

///
/// Close the game in a clean manner.
///
void close_game(game_t *game);

///
/// Set game view
///
void set_game_view(game_t *game, sfView *view);

///
/// Reset the game events.
///
void reset_game_events(game_t *game);

///
/// Basically an sfClock that can be paused
///
typedef struct pausable_clock {
    game_t *game;
    sfClock *frame_clock;
    float time;
    sfBool is_paused;
    sfBool has_game_pause;
} pausable_clock_t;

///
/// Create a clock that can be paused.
///
pausable_clock_t *create_pausable_clock(game_t *game);

///
/// Update the clock time.
///
float tick_pausable_clock(pausable_clock_t *clock);

///
/// Destroy the clock that can be paused.
///
void destroy_pausable_clock(pausable_clock_t *clock);

///
/// Restart the clock.
///
void restart_pausable_clock(pausable_clock_t *clock);

#endif //DISTRACT_GAME_H
