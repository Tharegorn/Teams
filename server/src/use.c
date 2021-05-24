/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** use
*/

#include "server.h"

void free_teams(server_t *s)
{
    if (s->l_cli->teams->teams != NULL) {
        free(s->l_cli->teams->teams);
        s->l_cli->teams->teams = NULL;
    }
    if (s->l_cli->teams->channel != NULL) {
        free(s->l_cli->teams->channel);
        s->l_cli->teams->channel = NULL;
    }
    if (s->l_cli->teams->thread != NULL) {
        free(s->l_cli->teams->thread);
        s->l_cli->teams->thread = NULL;
    }
}

void use_two(server_t *s, char **arr)
{
    if (arr[3] == NULL) {
        s->l_cli->contex = CHANNEL;
        s->l_cli->teams->teams = strdup(arr[1]);
        s->l_cli->teams->channel = strdup(arr[2]);
    } else if (arr[4] == NULL) {
        s->l_cli->contex = THREAD;
        s->l_cli->teams->teams = strdup(arr[1]);
        s->l_cli->teams->channel = strdup(arr[2]);
        s->l_cli->teams->thread = strdup(arr[3]);
    }
}

void use(server_t *s, char **arr)
{
    free_teams(s);
    if (arr[1] == NULL) {
        s->l_cli->contex = ANY;
    } else if (arr[2] == NULL) {
        s->l_cli->contex = TEAM;
        s->l_cli->teams->teams = strdup(arr[1]);
    } else
        use_two(s, arr);
}