/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** unsubscribe
*/

#include "server.h"

void rewrite_user(server_t *s)
{
    FILE *tmp = fopen("tmp", "r+");
    FILE *fd;
    char *line = NULL;
    size_t size = 0;

    remove(s->l_cli->u_uuid);
    fd = fopen(s->l_cli->u_uuid, "w+");
    while (getline(&line, &size, tmp) != -1)
        fprintf(fd, "%s", line);
    fclose(fd);
    fclose(tmp);
    free(line);
    remove("tmp");
}

void remove_user(server_t *s, char **arr)
{
    FILE *tmp = fopen("tmp", "w+");
    FILE *fd = fopen(s->l_cli->u_uuid, "r+");
    char *line = NULL;
    size_t size = 0;
    char **array = NULL;

    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        if (strcmp(array[0], arr[1]) != 0)
            fprintf(tmp, "%s", line);
    }
    fclose(fd);
    fclose(tmp);
    free(line);
    rewrite_user(s);
}

void rewrite_team(void)
{
    FILE *tmp = fopen("tmp", "r+");
    FILE *fd;
    char *line = NULL;
    size_t size = 0;

    remove("subscribe");
    fd = fopen("subscribe", "w+");
    while (getline(&line, &size, tmp) != -1)
        fprintf(fd, "%s", line);
    fclose(fd);
    fclose(tmp);
    free(line);
    remove("tmp");
}

void remove_team(char *user)
{
    FILE *tmp = fopen("tmp", "w+");
    FILE *fd = fopen("subscribe", "r+");
    char *line = NULL;
    size_t size = 0;
    char **array = NULL;

    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        if (strcmp(array[1], user) != 0)
            fprintf(tmp, "%s", line);
    }
    fclose(fd);
    fclose(tmp);
    free(line);
    rewrite_team();
}

void unsubscribe(server_t *s, char **arr)
{
    if (team_exists(arr[1]) == 1) {
        dprintf(s->l_cli->fd, "CREATE TEAM UNKNOW \"%s\"\n", arr[1]);
        return;
    }
    chdir("./server/logs/USERS/");
    if (access(s->l_cli->u_uuid, F_OK) == 1 || already_sub(s, arr[1]) == 0) {
        dprintf(s->l_cli->fd, "SUB UNAUTH\n");
        chdir("../../../");
        return;
    }
    remove_user(s, arr);
    chdir("../../../");
    chdir("./server/logs/teams/");
    chdir(arr[1]);
    remove_team(s->l_cli->u_uuid);
    chdir("../../../../");
    dprintf(s->l_cli->fd, "UNSUB %s %s", s->l_cli->u_uuid, arr[1]);
    server_event_user_unsubscribed(arr[1], s->l_cli->u_uuid);
}
