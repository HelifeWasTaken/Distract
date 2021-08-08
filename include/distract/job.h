/*
** EPITECH PROJECT, 2021
** distract_job
** File description:
** Source code
*/

#ifndef DISTRACT_JOB_H
#define DISTRACT_JOB_H

#include <stdbool.h>
#include <SFML/System.h>

typedef struct distract_job_message {
    int type;
    void *content;
} distract_job_message_t;

typedef struct distract_job {
    sfMutex *mutex;
    sfThread *thread;
    void *data;
    void (*action)(struct distract_job *distract_job);
    unsigned char messages_count;
    distract_job_message_t messages[256];
    bool in_progress;
} distract_job_t;

/**
 * @brief Initialize a job
 *
 * @param distract_job A job.
 */
static inline void start_distract_job(distract_job_t *distract_job)
{
    sfThread_launch(distract_job->thread);
}

/**
 * @brief Stop the job given
 *
 * @param distract_job A job.
 */
static inline void stop_distract_job(distract_job_t *distract_job)
{
    sfThread_terminate(distract_job->thread);
}

/**
 * @brief wait for the job to finish (it is an equivalent to await in C++)
 *
 * @param distract_job A job.
 */
static inline void wait_distract_job(distract_job_t *distract_job)
{
    sfThread_wait(distract_job->thread);
}

/**
 * @brief Create a distract job object
 *
 * @param action Function pointer to do the action
 * @param data Any data to pass to the action
 * @return distract_job_t*  A pointer to the created job
 */
distract_job_t *create_distract_job(void (*action)(distract_job_t *distract_job), void *data);

/**
 * @brief destory a job
 *
 * @param distract_job A job.
 */
void destroy_distract_job(distract_job_t *distract_job);

/**
 * @brief Send a message to the job
 *
 * @param distract_job A job.
 * @param type Type of the message
 * @param content Content of the message
 * @return false Failed to send the message
 * @return true Succesfully send the message
 */
bool send_distract_job_message(distract_job_t *distract_job, int type, void *content);

/**
 * @brief poll a message from the job
 *
 * @param distract_job A job.
 * @param type Type of the message
 * @return void* rtfm
 */
void *poll_distract_job_message(distract_job_t *distract_job, int type);

#endif
