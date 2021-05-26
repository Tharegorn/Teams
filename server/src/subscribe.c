/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** subscribe
*/

#include "server.h"

int already_sub(server_t *s, char *name)
{
    FILE *fd = fopen(s->l_cli->u_uuid, "r+");
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;

    while (getline(&line, &size, fd) != -1) {
        if (strcmp(arr[0], name) == 0) {
            fclose(fd);
            free(line);
            return 1;
        }
    }
    fclose(fd);
    free(line);
    return 0;
}

void fill_team_side(server_t *s, char *name)
{
    FILE *fd;

    chdir("./server/logs/teams/");
    chdir(name);
    fd = fopen("subscribe", "a");
    fprintf(fd, "\"%s\" \"%s\"\n", s->l_cli->name, s->l_cli->u_uuid);
    chdir("../../../../");
    fclose(fd);
}

void sub(server_t *s, char **arr)
{
    FILE *fd;

    if (team_exists(arr[1]) == 1) {
        dprintf(s->l_cli->fd, "CREATE TEAM UNKNOW \"%s\"\n", arr[1]);
        return;
    }
    chdir("./server/logs/USERS/");
    if( access( s->l_cli->u_uuid, F_OK ) == 0 ) {
        if (already_sub(s, arr[1]) == 1)
            return;
        fd = fopen(s->l_cli->u_uuid, "a");
    } else
        fd = fopen(s->l_cli->u_uuid, "w+");
    chdir("../../../");
    fill_team_side(s, arr[1]);
    server_event_user_subscribed(arr[1], s->l_cli->u_uuid);
    fprintf(fd, "\"%s\"\n", arr[1]);
    dprintf(s->l_cli->fd, "SUB \"%s\"\n", arr[1]);
    fclose(fd);
}
