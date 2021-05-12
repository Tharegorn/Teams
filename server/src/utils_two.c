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