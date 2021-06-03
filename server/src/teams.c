/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** teams
*/

#include "server.h"

int teams_exists(char *name)
{
    char *line = NULL;
    char **arr = NULL;
    FILE *fd = fopen("./server/logs/teams_uuid.log", "r+");
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

void contact_all(server_t *s, char **arr, char *uuid)
{
    int pos = s->l_cli->position;

    go_prev(s);
    for(; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
        if (s->l_cli->log_status == YES && s->l_cli->position == pos) {
            dprintf(s->l_cli->fd, "LIST TEAM \"%s\" \"%s\" \"%s\"\n",
            uuid, arr[0], arr[2]);
        } else if (s->l_cli->log_status == YES) {
            dprintf(s->l_cli->fd, "CREATE TEAM \"%s\" \"%s\" \"%s\"\n", uuid,
            arr[1], arr[2]);
        }
    }
    go_prev(s);
    for(; s->l_cli->next != NULL; s->l_cli = s->l_cli->next)
        if (s->l_cli->position == pos)
            break;
}

void create_sub(char *uuid)
{
    FILE *fd;

    chdir("./server/logs/teams/");
    chdir(uuid);
    fd = fopen("subscribe", "w+");
    fclose(fd);
    chdir("../../../../");
}

void create_team(server_t *s, char **arr)
{
    char *uuid = gen_uuid();

    if (strlen(arr[1]) <= 32 && strlen(arr[2]) <= 255 &&
    teams_exists(arr[1]) == 1) {
        add_team(uuid, arr[1], arr[2], s->l_cli->u_uuid);
        create_sub(uuid);
        contact_all(s, arr, uuid);
    } else
        dprintf(s->l_cli->fd, "CREATE ERROR\n");
    free(uuid);
}
