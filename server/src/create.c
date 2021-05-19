/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** create
*/

#include "server.h"

int teams_exists(char *name)
{
    FILE *fd = fopen("./server/logs/teams_uuid.log", "r+");
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;

    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[0], name) == 0) {
            free(line);
            fclose(fd);
            return 0;
        }
    }
    free(line);
    fclose(fd);
    return 1;
}

void add_team(char *uuid, char *name, char *description, char *u_uuid)
{
    FILE *fd = fopen("./server/logs/teams_uuid.log", "a");

    fprintf(fd, "\"%s\" \"%s\" \"%s\"\n", name, uuid, description);
    server_event_team_created(uuid, name, u_uuid);
    fclose(fd);
}

void create_team(char **arr, char *user_uuid)
{
    if (strlen(arr[1]) <= 32 && strlen(arr[2]) <= 255 &&\
     teams_exists(arr[1]) == 1) {
        add_team(gen_uuid(), arr[1], arr[2], user_uuid);
    } else
        return;
}

void create(server_t *s, char **arr)
{
    if (s->list_clients->contex == ANY && arr[2] == NULL) {
        return;
    } else {
        create_team(arr, s->list_clients->user_uuid);
    }
}