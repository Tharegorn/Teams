/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** list
*/

#include "server.h"

void list_teams(server_t *s)
{
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd = fopen("./server/logs/teams_uuid.log", "r+");

    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        dprintf(s->l_cli->fd, "LIST TEAM \"%s\" \"%s\" \"%s\"\n",
        arr[1], arr[0], arr[2]);
        usleep(0.1);
    }
    free(line);
    fclose(fd);
}

void list_chan(server_t *s)
{
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    fd = fopen("list_chans", "r+");
    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        dprintf(s->l_cli->fd, "LIST CHAN \"%s\" \"%s\" \"%s\"\n",
        arr[1], arr[0], arr[2]);
        usleep(0.1);
    }
    chdir("../../../../");
    free(line);
    fclose(fd);
}

void list_th(server_t *s)
{
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    chdir(s->l_cli->teams->channel);
    fd = fopen("list_threads", "r+");
    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        dprintf(s->l_cli->fd, "LIST TH \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
        arr[1], arr[4], arr[3], arr[0], arr[2]);
        usleep(0.1);
    }
    chdir("../../../../../");
    free(line);
    fclose(fd);
}

void list_rep(server_t *s)
{
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    chdir(s->l_cli->teams->channel);
    chdir(s->l_cli->teams->thread);
    fd = fopen("replies", "r+");
    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        dprintf(s->l_cli->fd, "LIST REP \"%s\" \"%s\" \"%s\" \"%s\"\n",
        arr[0], arr[1], arr[2], arr[3]);
        usleep(0.1);
    }
    chdir("../../../../../../");
    free(line);
    fclose(fd);
}

void list(server_t *s, __attribute__((unused))char **array)
{
    if (check_params(s) == 1)
        return;
    if (s->l_cli->contex == ANY)
        list_teams(s);
    if (s->l_cli->contex == TEAM)
        list_chan(s);
    if (s->l_cli->contex == CHANNEL)
        list_th(s);
    if (s->l_cli->contex == THREAD)
        list_rep(s);
}
