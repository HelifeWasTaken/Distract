/*
** EPITECH PROJECT, 2020
** entity
** File description:
** Source code
*/

#ifndef DISTRACT_ENTITY_H
#define DISTRACT_ENTITY_H
#include "SFML/Graphics.h"
#include "SFML/System.h"
#include "distract/game.h"
#include "distract/def.h"
#include "stdio.h"

///
/// Living entity in the distract_scene
///
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

///
/// Informations about an entity, in the entities registry
///
typedef struct entity_info {
    struct entity_info *next;
    int type;
    bool (*create)(game_t *game, entity_t *entity);
    void (*draw)(game_t *game, entity_t *entity);
    void (*destroy)(game_t *game, entity_t *entity);
    void (*update)(game_t *game, entity_t *entity);
    bool (*handle_event)(game_t *game, entity_t *entity, sfEvent *event);
} entity_info_t;

#define ENTITY(type, ...) \
    (entity_info_t) { NULL, type, __VA_ARGS__ }

///
/// Create the entity of specified type.
///
entity_t *create_entity(game_t *game, int type);

///
/// Get entity info from its type.
///
entity_info_t *get_entity_info(game_t *game, int type);

///
/// Register an entity to the registry.
///
bool register_entity(game_t *game, const entity_info_t *entity);

///
/// Add a detached or externally allocated entity to the distract_scene entities.
///
void add_to_entities(game_t *game, entity_t *entity);

///
/// Register several entities to the registry.
///
bool register_entities(game_t *game, entity_info_t **entities);

///
/// Call the draw function of the entity.
///
void draw_entity(game_t *game, entity_t *entity);

///
/// Call the update function of the entity.
///
void update_entity(game_t *game, entity_t *entity);

///
/// Call the update function of the entity using the thread.
///
void update_entity_async(game_t *game, entity_t *entity);

///
/// Deallocate an entity.
/// Calls the destroy function of the entity.
///
void destroy_entity(game_t *game, entity_t *entity);

#define REGISTER_ENTITIES(game, ...) \
    register_entities(game, ((entity_info_t *[]){ 0, ## __VA_ARGS__, NULL })+1)

///
/// Sorts the entities in the distract_scene.
/// Is called automatically when create_entity is called.
///
void sort_entities(game_t *game);

///
/// Get the next entity in the list that matches the specified type.
///
/// You may want to use the GET_ENTITY(game, type) macro or
/// FOREACH_ENTITY_OF_TYPE(...) {} instead.
///
entity_t *get_next_entity_of_type(entity_t *entity, int type);

///
/// Get the entity in the list that matches the specified type
///
/// You may want to use the GET_ENTITY(game, type) macro or
/// FOREACH_ENTITY_OF_TYPE(...) {} instead.
///
entity_t *get_entity(game_t *game, int type);

///
/// Get the instance of an entity in the list that matches the specified type
///
void *get_instance(game_t *game, int type);

///
/// You may want to use `get_entity(game, entity_type)` method instead.
///
#define GET_ENTITY(game, entity_type) \
    fprintf(stderr, "GET_ENTITY macro is deprecated please use" \
                    "get_entity(game, entity_type) method instead"); \
    abort()

///
/// Call the following instruction block each time.
///
/// If you don't have an list of entities for the second argument,
/// put `game->distract_scene->entities`.
///
/// The third argument will be the name of the newly created variable.
///
#define FOREACH_ENTITY_OF_TYPE(entity_type, entities, entity) \
    for (entity_t *entity = (entities->type == entity_type ? entities \
        : get_next_entity_of_type(entities, entity_type)) \
        ; entity != NULL; \
        entity = get_next_entity_of_type(entity, entity_type))

///
/// Move the entity towards the target position.
/// Movement will be of the specified distance.
///
sfVector2f move_entity_towards(entity_t *entity, sfVector2f target,
    float distance);

///
/// Informations passed to the underlying thread.
///
typedef struct thread_info {
    sfThread *thread;
    game_t *game;
    entity_t *entity;
} thread_info_t;

#endif //DISTRACT_ENTITY_H