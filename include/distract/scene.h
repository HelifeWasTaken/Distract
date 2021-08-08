/*
** EPITECH PROJECT, 2020
** distract_scene
** File description:
** Source code
*/

#ifndef DISTRACT_SCENE_H
#define DISTRACT_SCENE_H
#include "distract/game.h"
#include "distract/hashmap.h"
#include "distract/def.h"
#include "stdbool.h"

typedef struct distract_scene_info {
    struct distract_scene_info *next;
    int id;
    int (*lifecycle)(game_t *game);
    void *storage;
} distract_scene_info_t;

typedef struct distract_scene {
    int id;
    distract_scene_info_t *info;
    struct entity *entities;
    distract_hashmap_t *distract_resources;
    struct gui_element *gui_elements;
    bool in_exit_state;
    int pending_distract_scene_id;
    void *storage;
} distract_scene_t;

///
/// Allocate distract_scene.
///
distract_scene_t *allocate_distract_scene(void);

///
/// Deallocate distract_scene.
///
void deallocate_distract_scene(distract_scene_t *distract_scene);

///
/// Push a distract_scene on top of the distract_scenes stack and await until the distract_scene exit.
///
int await_distract_scene(game_t *game, int distract_scene_id);

///
/// Call the draw function of every entities in the distract_scene.
///
void draw_distract_scene(game_t *game);

///
/// Call the update function of every entities in the distract_scene.
///
void update_distract_scene(game_t *game);

///
/// Destroy every entities in the distract_scene.
/// Calls the destroy function of every entities in the distract_scene.
/// If destroy_distract_resources is set to true, registered distract_resources will also be
/// freed.
///
void destroy_distract_scene(game_t *game, bool destroy_distract_resources);

///
/// Check if window is still open and distract_scene is not exited.
///
bool is_distract_scene_updated(game_t *game);

///
/// Exit the current distract_scene and open the distract_scene specified by the id.
///
void switch_to_distract_scene(game_t *game, int id);

///
/// Set the distract_scene to open when the current distract_scene is closed.
///
void set_pending_distract_scene(game_t *game, int id);

///
/// Check there is a distract_scene that will be open once the current distract_scene is closed.
///
bool has_pending_distract_scene(game_t *game);

///
/// Registers a distract_scene in the distract_scene registry.
///
bool register_distract_scene(game_t *game, int id, int (*lifecycle)(game_t *game));

///
/// Get distract_scene info.
///
distract_scene_info_t *get_distract_scene_info(game_t *game, int id);

///
/// Execute the distract_scene lifecycle of the pending distract_scene.
///
int load_pending_distract_scene(game_t *game);


///
/// Registers multiple distract_scenes in the distract_scene registry.
/// count is the number of distract_scenes to register.
///
void register_distract_scenes(game_t *game, int count, ...);

///
/// Send event to every entities in the distract_scenes until one of the entities event
/// handlers return true.
///
bool transmit_event_to_distract_scene(game_t *game, sfEvent *event);

#define REGISTEDR_SCENES(game, ...) \
    register_distract_scenes(game, ARGS_COUNT(__VA_ARGS__), # __VA_ARGS__)

#endif //DISTRACT_SCENE_H
