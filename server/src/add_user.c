/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** add_user
*/

#include "server.h"

void display_all(server_t *s, char *uuid, char *name)
{
    int position = s->l_cli->position;

    dprintf(s->l_cli->fd, "LOGIN CREATE \"%s\" \"%s\"\n",
    s->l_cli->u_uuid, s->l_cli->name);
    go_prev(s);
    for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
        if (s->l_cli->log_status == YES && s->l_cli->position != position)
            dprintf(s->l_cli->fd, "LOGIN DISPLAY \"%s\" \"%s\"\n", uuid, name);
    }
    go_prev(s);
    for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
        if (s->l_cli->position == position)
            break;
    }
}

void add_user_two(server_t *s, char **arr, char **array, int res)
{
    FILE *fd = fopen("./server/logs/user_uuid.log", "a");

    if (res == 1) {
        s->l_cli->name = strdup(array[0]);
        s->l_cli->u_uuid = strdup(array[1]);
    } else {
        s->l_cli->name = strdup(arr[1]);
        s->l_cli->u_uuid = strdup(gen_uuid());
        fprintf(fd, "\"%s\" \"%s\"\n", s->l_cli->name,
        s->l_cli->u_uuid);
        server_event_user_created(s->l_cli->u_uuid,
        s->l_cli->name);
    }
    server_event_user_logged_in(s->l_cli->u_uuid);
    display_all(s, s->l_cli->u_uuid, s->l_cli->name);
}

void add_user(server_t *s, char **arr)
{
    char *line = NULL;
    char **array = NULL;
    int res = 0;
    size_t size = 0;
    FILE *fd = fopen("./server/logs/user_uuid.log", "r+");

    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        if (strcmp(arr[1], array[0]) == 0) {
            res = 1;
            break;
        }
    }
    fclose(fd);
    s->l_cli->log_status = YES;
    add_user_two(s, arr, array, res);
    info_free(fd, line, arr);
}
