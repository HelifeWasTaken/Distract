/*
** EPITECH PROJECT, 2020
** debug
** File description:
** Source code
*/

#ifndef DISTRACT_DEBUG_H
    #define DISTRACT_DEBUG_H

    // Print error if var is equivalent to unexpect and return the retv
    #define D_ASSERT(var, unexpect, error, retv) \
        if ((var) == (unexpect)) { \
            fprintf(stderr, (error)); \
            return ((retv)); \
        }

#endif //DISTRACT_DEBUG_H
