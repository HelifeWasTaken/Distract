/*
** EPITECH PROJECT, 2021
** input
** File description:
** Source code
*/

#ifndef DISTRACT_INPUT_H
#define DISTRACT_INPUT_H

#include <SFML/Window/Event.h>
#include <stdbool.h>

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

typedef struct keyboard_input {
    bool is_being_pressed;
    bool is_pressed;
    bool is_being_released;
    bool was_pressed;
} keyboard_input_t;

typedef struct input {
    struct keyboard_input keys[sfKeyCount];
} input_t;

/**
 * @brief Get the input key
 *
 * @param input The input stock
 * @param event The event to get the key from
 */
void on_keyboard_input(input_t *input, sfKeyEvent *event);

/**
 * @brief Update the input state of the keyboard.
 *
 * @param input
 */
void update_input(input_t *input);

/**
 * @brief Called when a key has a event occuring.
 *
 * @param input
 * @param event
 */
void on_input(input_t *input, sfEvent *event);

/**
 * @brief Updating the input state of the keyboard.
 *
 * @param input
 */
void update_keyboard_input(input_t *input);

/**
 * @brief Get the input state of the key code.
 *
 * @param input
 * @param keycode
 * @return keyboard_input_t
 */
keyboard_input_t get_input_key(input_t *input, sfKeyCode keycode);

#define START_ARROW_KEY sfKeyLeft
#define END_ARROW_KEY sfKeyDown

#include <SFML/Graphics/RenderWindow.h>
/**
 * @brief Get the mouse pos object from the view pixel size and relative to the window.
 *
 * @return sfVector2f
 */
sfVector2f get_mouse_pos(sfRenderWindow *window, sfView *view);

#endif