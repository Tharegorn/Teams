/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** use
*/

#include "server.h"

void free_teams(server_t *s)
{
    if (s->list_clients->teams->teams == NULL)
        free(s->list_clients->teams->teams);
    if (s->list_clients->teams->channel == NULL)
        free(s->list_clients->teams->channel);
    if (s->list_clients->teams->thread == NULL)
        free(s->list_clients->teams->thread);
}

int team_exists(char *uuid)
{
    FILE *fd = fopen("./server/logs/teams_uuid.log", "r+");
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;

    while (getline(&line, &size, fd) != -1)
    {
        arr = str_warray(line, ' ');
        if (strcmp(arr[1], uuid) == 0)
        {
            free(line);
            fclose(fd);
            return 0;
        }
    }
    free(line);
    fclose(fd);
    return 1;
}

void use(server_t *s, char **arr)
{
    if (arr[1] == NULL)
    {
        free_teams(s);
        s->list_clients->contex = ANY;
    }
    else if (arr[2] == NULL)
    {
        if (team_exists(arr[1]) == 1)
            dprintf(s->list_clients->fd, "USE TEAM NULL %s", arr[1]);
        else
        {
            s->list_clients->contex = TEAM;
            free_teams(s);
            s->list_clients->teams->teams = strdup(arr[1]);
        }
    }
}
