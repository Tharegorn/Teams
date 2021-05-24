/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** logout
*/

#include "server.h"

void logout(server_t *s, __attribute__((unused))char **arr)
{
    int position = s->l_cli->position;
    char *uuid = s->l_cli->u_uuid;
    char *name = s->l_cli->name;

    if (s->l_cli->log_status == NO)
        return;
    server_event_user_logged_out(s->l_cli->u_uuid);
    go_prev(s);
    for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
        if (s->l_cli->log_status == YES && s->l_cli->position != position)
            dprintf(s->l_cli->fd, "LOGOUT DISPLAY \"%s\" \"%s\"", uuid, name);
    }
    go_prev(s);
    for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
        if (s->l_cli->position == position)
            break;
    }
    close(s->l_cli->fd);
    s->l_cli->fd = 0;
    free(s->l_cli->name);
    free(s->l_cli->u_uuid);
    s->l_cli->log_status = NO;
    s->l_cli->contex = ANY;
}
