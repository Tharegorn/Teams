/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** info
*/

#include "server.h"

void info_user(server_t *s)
{
    char *line = NULL;
    char **arr = NULL;
    int pos = s->l_cli->position;
    int on = 0;
    size_t size = 0;
    FILE *fd = fopen("./server/logs/user_uuid.log", "r+");

    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        go_prev(s);
        on = is_online(s, arr[1]);
        go_pos(pos, s);
        dprintf(s->l_cli->fd, "USER %s %s %d\n", arr[1], arr[0], on);
        usleep(0.1);
    }
    free(line);
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    fclose(fd);
}

void info_team(server_t *s)
{
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd = fopen("./server/logs/teams_uuid.log", "r+");

    while(getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[1], s->l_cli->teams->teams) == 0)
            dprintf(s->l_cli->fd, "INFO TEAM \"%s\" \"%s\" \"%s\"\n", arr[1],
            arr[0], arr[2]);
    }
    free(line);
    fclose(fd);
}

void info_chan(server_t *s)
{
    char *line;
    char **arr;
    size_t size = 0;
    FILE *fd;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    fd = fopen("list_chans", "r+");
    while(getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[1], s->l_cli->teams->channel) == 0)
            dprintf(s->l_cli->fd, "INFO CHAN \"%s\" \"%s\" \"%s\"\n", arr[1],
            arr[0], arr[2]);
    }
    chdir("../../../../");
    free(line);
    fclose(fd);
}

void info_thread(server_t *s)
{
    FILE *fd;
    char *line;
    char **arr;
    size_t size = 0;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    chdir(s->l_cli->teams->channel);
    fd = fopen("list_threads", "r+");
    while(getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[1], s->l_cli->teams->thread) == 0)
            dprintf(s->l_cli->fd,
            "INFO TH \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",
            arr[1], arr[4], arr[3], arr[0], arr[2]);
    }
    chdir("../../../../../");
    free(line);
    fclose(fd);
}

void info(server_t *s, __attribute__((unused))char **arr)
{
    if (check_params(s) == 1)
        return;
    if (s->l_cli->contex == ANY)
        info_user(s);
    if (s->l_cli->contex == TEAM)
        info_team(s);
    if (s->l_cli->contex == CHANNEL)
        info_chan(s);
    if (s->l_cli->contex == THREAD)
        info_thread(s);
}