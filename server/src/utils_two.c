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
    for (; s->l_cli->prev != NULL;\
     s->l_cli = s->l_cli->prev);
}

void set_team_to_null(server_t *s)
{
    s->l_cli->teams = malloc(sizeof(teams_t));
    s->l_cli->teams->teams = NULL;
    s->l_cli->teams->channel = NULL;
    s->l_cli->teams->thread = NULL;
}

void set_clients(server_t *s)
{
    load_users();
    s->l_cli = malloc(sizeof(client_t));
    s->l_cli->prev = NULL;
    for (int i = 0; i < 30; i++, s->l_cli = s->l_cli->next) {
        s->l_cli->fd = 0;
        s->l_cli->log_status = NO;
        s->l_cli->next = malloc(sizeof(client_t));
        s->l_cli->next->next = NULL;
        s->l_cli->next->prev = s->l_cli;
        s->l_cli->position = i;
        s->l_cli->contex = ANY;
        set_team_to_null(s);
    }
    go_prev(s);
}
