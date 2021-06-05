/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** subscribed
*/

#include "server.h"

void list_users(server_t *s, int clifd, char *team)
{
    FILE *fd;
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;

    chdir("./server/logs/teams/");
    chdir(team);
    fd = fopen("subscribe", "r+");
    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        dprintf(clifd, "USERS %s %s %d\n", arr[1], arr[0],
                get_status(s, arr[1], s->l_cli->position));
        usleep(0.1);
    }
    fclose(fd);
    free(line);
    chdir("../../../../");
}

void subscribed(server_t *s, char **arr)
{
    if (arr[1] == NULL);
    else if (team_exists(arr[1]) == 0)
        list_users(s, s->l_cli->fd, arr[1]);
    else
        dprintf(s->l_cli->fd, "CREATE UNKNOWN\n");
}
