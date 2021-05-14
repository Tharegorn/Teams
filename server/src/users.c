/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** users
*/

#include "server.h"

void go_pos(int pos, server_t *s)
{
    for (; s->list_clients->next != NULL;\
    s->list_clients = s->list_clients->next) {
        if (s->list_clients->position == pos)
            break;
    }
}

int is_online(server_t *s, char *uuid)
{
    go_prev(s);
    for (; s->list_clients->next != NULL;\
    s->list_clients = s->list_clients->next) {
        if (strcmp(s->list_clients->user_uuid, uuid) == 0) {
            go_prev(s);
            return 0;
        }
    }
    go_prev(s);
    return 1;
}

void users(server_t *s)
{
    FILE *fd = fopen("./server/logs/user_uuid.log", "r+");
    char *line;
    char **arr;
    size_t size = 0;
    int pos = s->list_clients->position;
    int on = 0;

    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        on = is_online(s, arr[1]);
        go_pos(pos, s);
        dprintf(s->list_clients->fd, "USERS %s %s %d\n", arr[1], arr[0], on);
        usleep(0.1);
    }
    free(line);
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    fclose(fd);
}