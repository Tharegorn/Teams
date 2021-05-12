/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** add_user
*/

#include "server.h"

void add_user_two(server_t *s, char **arr, char **array, int res)
{
    FILE *fd = fopen("./server/logs/user_uuid.log", "a");

    if (res == 1) {
        s->list_clients->name = strdup(array[0]);
        s->list_clients->user_uuid = strdup(array[1]);
    } else {
        s->list_clients->name = strdup(arr[1]);
        s->list_clients->user_uuid = strdup(gen_uuid());
        fputs(s->list_clients->name, fd);
        fputs(" ", fd);
        fputs(s->list_clients->user_uuid, fd);
        fputs("\n", fd);
        server_event_user_created(s->list_clients->user_uuid,\
         s->list_clients->name);
    }
}

void add_user(server_t *s, char **arr)
{
    char *line = NULL;
    char **array = NULL;
    size_t size = 0;
    int res = 0;
    FILE *fd = fopen("./server/logs/user_uuid.log", "r+");

    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        if (strcmp(arr[1], array[0]) == 0) {
            res = 1;
            break;
        }
    }
    fclose(fd);
    add_user_two(s, arr, array, res);
    server_event_user_logged_in(s->list_clients->user_uuid);
    s->list_clients->log_status = YES;
    dprintf(s->list_clients->fd, "LOGIN %s %s",\
    s->list_clients->user_uuid, s->list_clients->name);
    info_free(fd, line, arr);
}