/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** create
*/

#include "server.h"

void create(server_t *s, char **arr)
{
    if (s->list_clients->contex == ANY && arr[2] != NULL) {
        create_team(arr, s->list_clients->user_uuid, s->list_clients->fd);
    } else if (s->list_clients->contex == TEAM && arr[2] != NULL)
        create_channel(s, arr);
}
