/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** teams
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
    struct stat st = {0};
    FILE *fd = fopen("./server/logs/teams_uuid.log", "a");
    FILE *list = NULL;

    chdir("./server/logs/teams/");
    fprintf(fd, "\"%s\" \"%s\" \"%s\"\n", name, uuid, description);
    if (stat(uuid, &st) == -1) {
        mkdir(uuid, 0700);
        chdir(uuid);
        list = fopen("list_chans", "w");
        chdir("../../../../");
        fclose(list);
    }
    server_event_team_created(uuid, name, u_uuid);
    fclose(fd);
}

void create_team(char **arr, char *u_uuid, int fd)
{
    char *uuid = gen_uuid();

    if (strlen(arr[1]) <= 32 && strlen(arr[2]) <= 255 &&\
     teams_exists(arr[1]) == 1) {
        add_team(uuid, arr[1], arr[2], u_uuid);
        dprintf(fd, "CREATE TEAM \"%s\" \"%s\" \"%s\"\n", uuid, arr[1], arr[2]);
    } else
        dprintf(fd, "CREATE ERROR\n");
    free(uuid);
}
