/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** users
*/

#include "server.h"

void go_pos(int pos, server_t *s)
{
    for (; s->l_cli->next != NULL;\
    s->l_cli = s->l_cli->next) {
        if (s->l_cli->position == pos)
            break;
    }
}

int is_online(server_t *s, char *uuid)
{
    for (; s->l_cli->next != NULL;\
    s->l_cli = s->l_cli->next) {
        if (s->l_cli->u_uuid != NULL && strcmp(s->l_cli->u_uuid, uuid) == 0) {
            go_prev(s);
            return 1;
        }
    }
    go_prev(s);
    return 0;
}

void users(server_t *s, __attribute__((unused))char **array)
{
    char *line;
    char **arr;
    int pos = s->l_cli->position;
    int on = 0;
    size_t size = 0;
    FILE *fd = fopen("./server/logs/user_uuid.log", "r+");

    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        go_prev(s);
        on = is_online(s, arr[1]);
        go_pos(pos, s);
        dprintf(s->l_cli->fd, "USERS \"%s\" \"%s\" %d\n", arr[1], arr[0], on);
        usleep(0.1);
    }
    free(line);
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    fclose(fd);
}
