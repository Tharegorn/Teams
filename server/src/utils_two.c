/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** utils_two
*/

#include "server.h"

client_t *create_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    client->fd = fd;
    return client;
}

void go_prev(server_t *s)
{
    for (; s->list_clients->prev != NULL;\
     s->list_clients = s->list_clients->prev);
}

void set_clients(server_t *s)
{
    load_users();
    s->list_clients = malloc(sizeof(client_t));
    s->list_clients->prev = NULL;
    for (int i = 0; i < 30; i++, s->list_clients = s->list_clients->next) {
        s->list_clients->fd = 0;
        s->list_clients->log_status = NO;
        s->list_clients->next = malloc(sizeof(client_t));
        s->list_clients->next->next = NULL;
        s->list_clients->next->prev = s->list_clients;
        s->list_clients->position = i;
    }
    go_prev(s);
}