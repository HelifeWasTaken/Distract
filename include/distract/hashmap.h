/*
** EPITECH PROJECT, 2021
** distract
** File description:
** distract_hashmap
*/

#ifndef DISTRACT_HASHMAP_H
#define DISTRACT_HASHMAP_H

#include <sys/types.h>
#include <stdbool.h>
#include "distract/util.h"

struct distract_hashmap_list {
    char *key;
    void *value;
    struct distract_hashmap_list *next;
};

struct distract_hashmap_bucket {
    struct distract_hashmap_list *data;
};

typedef struct distract_hashmap {
    size_t size;
    size_t capacity;
    struct distract_hashmap_bucket *bucket;
    size_t (*hasher)(struct distract_hashmap *map, void *key);
} distract_hashmap_t;

/**
 * @brief Create an empty hashmap.
 *
 * @param capacity The initial capacity of the hashmap.
 * @param hasher A function pointer to a function that returns a hash value
 * @return distract_hashmap_t*
 */
distract_hashmap_t *distract_hashmap_create(size_t capacity,
        size_t (*hasher)(distract_hashmap_t *map, void *key));

/**
 * @brief Destroy the hashmap
 *
 * @param hash_map The hashmap to destroy
 */
void distract_hashmap_destroy(distract_hashmap_t *hash_map);

/**
 * @brief Set a value in the hashmap.
 *
 * @param hash_map_ptr A pointer to the hashmap
 * @param key
 * @param value
 * @return int The size of the hashmap if it was successfully set, -1 otherwise
 */
int distract_hashmap_set(distract_hashmap_t **hash_map_ptr, void *key, void *value);

/**
 * @brief Unset a value in the hashmap.
 *
 * @param map_ptr A pointer to the hashmap
 * @param key The key to unset
 */
void distract_hashmap_unset(distract_hashmap_t **map_ptr, void *key);

/**
 * @brief Get a value from the hashmap.
 *
 * @param hash_map A pointer to the hashmap
 * @param key
 * @return void* A pointer to the value if it was found, NULL otherwise
 */
void *distract_hashmap_get(distract_hashmap_t *hash_map, void *key);

/**
 * @brief Get the size of the hashmap by system of getindex pardigm.
 *
 * @param hash_map
 * @param key
 * @return void*
 */
void *distract_hashmap_getindex(distract_hashmap_t *hash_map, void *key);

/**
 * @brief Resize the hashmap.
 *
 * @param hash_map_ptr
 * @return int The size of the hashmap if it was successfully resized, -1 otherwise
 */
int distract_hashmap_resize(distract_hashmap_t **hash_map_ptr);

/**
 * @brief Insert to head of bucket of the hashmap got by hashing (it is considered as a private function)
 *
 * @param list
 * @param node
 * @return true Allocated memory, false otherwise
 * @return false A node with the same key already exists or memory allocation error
 */
bool insert_distract_hashmap_bucket_front(struct distract_hashmap_list **list,
    struct distract_hashmap_list *node);

/**
 * @brief Create a new node by the one passed as argument.
 *
 * @param new Generally created statically and passed as args like &(some_struct_t){value1, value2, ... }
 * @return struct distract_hashmap_list*
 */
struct distract_hashmap_list *distract_hashmap_create_node(struct distract_hashmap_list *new);

/**
 * @brief Check if it is needed to resize the hashmap.
 *
 * @param self A pointer to the hashmap
 * @return true Sucesfully resized, false otherwise
 * @return false A memory allocation error has append
 */
bool check_need_resize_distract_hashmap(distract_hashmap_t **self);

#endif
