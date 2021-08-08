/*
** EPITECH PROJECT, 2021
** distract_job
** File description:
** Source code
*/

#include <stdio.h>
#include "distract/job.h"
#include <SFML/System.h>
#include <SFML/System/Mutex.h>
#include <SFML/System/Sleep.h>
#include <SFML/System/Thread.h>
#include <SFML/System/Types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <distract/util.h>
#include <distract/debug.h>

static void run_distract_job(void *raw_distract_job)
{
    distract_job_t *distract_job = raw_distract_job;

    sfMutex_lock(distract_job->mutex);
    distract_job->in_progress = true;
    sfMutex_unlock(distract_job->mutex);
    distract_job->action(distract_job);
    sfMutex_lock(distract_job->mutex);
    distract_job->in_progress = false;
    sfMutex_unlock(distract_job->mutex);
}

distract_job_t *create_distract_job(void (*action)(distract_job_t *distract_job), void *data)
{
    distract_job_t *distract_job = calloc(1, sizeof(distract_job_t));

    if (distract_job == NULL)
        return (NULL);
    distract_job->data = data;
    distract_job->action = action;
    distract_job->messages_count = 0;
    distract_job->in_progress = false;
    distract_job->thread = sfThread_create(&run_distract_job, distract_job);
    distract_job->mutex = sfMutex_create();
    if (distract_job->thread == NULL || distract_job->mutex == NULL) {
        free(distract_job);
        return (NULL);
    }
    for (int i = 0; i < 255; i++)
        distract_job->messages[i].type = -1;
    return (distract_job);
}

void destroy_distract_job(distract_job_t *distract_job)
{
    sfThread_destroy(distract_job->thread);
    sfMutex_destroy(distract_job->mutex);
    free(distract_job);
}

bool send_distract_job_message(distract_job_t *distract_job, int type, void *content)
{
    if (content == NULL)
        fprintf(stderr, "Your distract_job message content is NULL! It is error prone!");
    sfMutex_lock(distract_job->mutex);
    if (distract_job->messages_count == 255) {
        sfMutex_unlock(distract_job->mutex);
        return (false);
    }
    distract_job->messages[distract_job->messages_count] = (distract_job_message_t) { type, content };
    distract_job->messages_count++;
    sfMutex_unlock(distract_job->mutex);
    return (true);
}

void *poll_distract_job_message(distract_job_t *distract_job, int type)
{
    int i = 0;
    void *content = NULL;

    sfMutex_lock(distract_job->mutex);
    for (i = 0; i < distract_job->messages_count; i++) {
        if (distract_job->messages[i].type == type)
            break;
    }
    if (i == distract_job->messages_count) {
        sfMutex_unlock(distract_job->mutex);
        return (NULL);
    }
    content = distract_job->messages[i].content;
    for (i++; i < distract_job->messages_count; i++)
        distract_job->messages[i - 1] = distract_job->messages[i];
    distract_job->messages[i - 1] = (distract_job_message_t) {-1, 0};
    distract_job->messages_count--;
    sfMutex_unlock(distract_job->mutex);
    return (content);
}
