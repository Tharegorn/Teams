/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** logout
*/

#include "server.h"

void logout(server_t *s, __attribute__((unused))char **arr)
{
    if (s->list_clients->log_status == NO)
        return;
    server_event_user_logged_out(s->list_clients->user_uuid);
    close(s->list_clients->fd);
    s->list_clients->fd = 0;
    free(s->list_clients->name);
    free(s->list_clients->user_uuid);
    s->list_clients->log_status = NO;
}