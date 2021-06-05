/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** create
*/

#include "server.h"

int team_exists(char *uuid)
{
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd = fopen("./server/logs/teams_uuid.log", "r+");

    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[1], uuid) == 0) {
            free(line);
            fclose(fd);
            return 0;
        }
    }
    free(line);
    fclose(fd);
    return 1;
}

int chan_exist(char *team, char *chan)
{
    chdir("./server/logs/teams/");
    chdir(team);
    if (chdir(chan) == -1) {
        chdir("../../../../");
        return 1;
    }
    chdir("../../../../../");
    return 0;
}

int thread_exist(char *team, char *chan, char *th)
{
    chdir("./server/logs/teams/");
    chdir(team);
    chdir(chan);
    if (chdir(th) == -1) {
        chdir("../../../../../");
        return 1;
    }
    chdir("../../../../../../");
    return 0;

}

int check_params(server_t *s)
{
    int i = s->l_cli->fd;

    if (s->l_cli->teams->teams != NULL) {
        if (team_exists(s->l_cli->teams->teams) == 1) {
            dprintf(i, "CREATE TEAM UNKNOW \"%s\"", s->l_cli->teams->teams);
            return 1;
        }
    }
    if (s->l_cli->teams->channel != NULL) {
        if (chan_exist(s->l_cli->teams->teams, s->l_cli->teams->channel) == 1) {
            dprintf(i, "CREATE CHAN UNKNOW \"%s\"", s->l_cli->teams->channel);
            return 1;
        }
    }
    if (s->l_cli->teams->thread != NULL) {
        if (thread_exist(s->l_cli->teams->teams, s->l_cli->teams->channel,
                         s->l_cli->teams->thread) == 1) {
            dprintf(i, "CREATE THREAD UNKNOW \"%s\"", s->l_cli->teams->thread);
            return 1;
        }
    }
    return 0;
}

void create(server_t *s, char **arr)
{
    if (check_params(s) == 1)
        return;
    if (s->l_cli->contex == ANY && arr[2] != NULL) {
        create_team(s, arr);
        return;
    }
    if (s->l_cli->contex == TEAM && arr[2] != NULL) {
        create_channel(s, arr);
        return;
    }
    if (s->l_cli->contex == CHANNEL && arr[2] != NULL) {
        create_thread(s, arr);
        return;
    }
    if (s->l_cli->contex == THREAD && arr[1] != NULL) {
        create_reply(s, arr);
        return;
    }
}
