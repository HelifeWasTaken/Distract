/*
** EPITECH PROJECT, 2021
** distract_hashmaplist
** File description:
** list
*/

#include "distract/hashmap.h"
#include <stdlib.h>

struct distract_hashmap_list *distract_hashmap_create_node(struct distract_hashmap_list *new)
{
    struct distract_hashmap_list *tmp = malloc(sizeof(struct distract_hashmap_list));

    if (tmp == NULL)
        return (NULL);
    tmp->key = new->key;
    tmp->value = new->value;
    tmp->next = NULL;
    return (tmp);
}

bool insert_distract_hashmap_bucket_front(struct distract_hashmap_list **list,
    struct distract_hashmap_list *node)
{
    struct distract_hashmap_list *new = distract_hashmap_create_node(node);

    if (new == NULL)
        return (false);
    new->next = *list;
    *list = new;
    return (true);
}
