/*
** EPITECH PROJECT, 2020
** MY_RPG_PUBLIC
** File description:
** distract_distract/animable.h
*/

#ifndef DISTRACT_ANIMABLE_H
    #define DISTRACT_ANIMABLE_H

    #include <SFML/System.h>
    #include <SFML/Graphics.h>
    #include <stdbool.h>

    ///
    /// \brief The ids of start and end of the animation.
    ///
    typedef struct distract_animation {
        int start_id;
        int end_id;
    } distract_animation_t;

    ///
    /// \brief The struct that represents an animable object.
    /// \param sprite The sprite of the object.
    /// \param distract_animations The animation of the object.
    /// \param frame_size The size of the sprite.
    /// \param frame_per_line The number of frames per line.
    ///
    typedef struct distract_animable_info {
        sfSprite *sprite;
        sfVector2f frame_size;
        int frames_per_line;
        distract_animation_t distract_animations[50];
    } distract_animable_info_t;

    ///
    /// \brief The struct that represents an animable object.
    /// \param current_distract_anima The current animation of the object.
    /// \param current_sheet_frame The current frame of the animation.
    /// \param info The struct that keeps the information of the object.
    ///
    typedef struct distract_animable {
        int current_distract_anim;
        int current_sheet_frame;
        distract_animable_info_t info;
    } distract_animable_t;

    ///
    /// \brief Set the distract animable frame
    /// \param distract_animable The struct that represents the object.
    /// \param id The id of the frame.
    ///
    void set_distract_animable_frame(distract_animable_t *distract_animable, int id);

    ///
    /// \brief Set the distract animable animation
    /// \param distract_animable The struct that represents the object.
    /// \param id The animation id to set.
    ///
    void set_distract_animable_distract_animation(distract_animable_t *distract_animable, int id);

    ///
    /// \brief Set the distract animable sheet frame
    /// \param distract_animable The struct that represents the object.
    /// \return The id of the distract animable.
    ///
    int get_distract_animable_frame(distract_animable_t *distract_animable);

    ///
    /// \brief Get distract animable distract animation
    /// \param distract_animable The struct that represents the object.
    /// \return The id of the distract animable.
    ///
    int get_distract_animable_distract_animation(distract_animable_t *distract_animable);

    ///
    /// \brief Tells you if the distract animable animation is done.
    /// \param distract_animable The struct that represents the object.
    /// \return true if the animation is done, false otherwise.
    ///
    bool is_distract_animation_done(distract_animable_t *distract_animable);

    ///
    /// \brief Set the distract animable info
    /// \param distract_animable The struct that represents the object.
    /// \param info The struct that keeps the information of the object.
    ///
    void set_distract_animable_info(distract_animable_t *distract_animable, distract_animable_info_t *info);

#endif
