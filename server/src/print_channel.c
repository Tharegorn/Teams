/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** print_channel
*/

#include "server.h"

void print_channel(server_t *s, char **a, char *uuid, int state)
{
    if (state == 0) {
        dprintf(s->l_cli->fd,
        "CREATE PRINT CHAN \"%s\" \"%s\" \"%s\"\n", uuid, a[1], a[2]);
    } else if (state == 1) {
        dprintf(s->l_cli->fd,
        "CREATE EVENT CHAN \"%s\" \"%s\" \"%s\"\n", uuid, a[1], a[2]);
    }
}

void logout_all(server_t *s)
{
    go_prev(s);
    for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
        if (s->l_cli->fd != 0) {
            if (s->l_cli->log_status == YES)
                server_event_user_logged_out(s->l_cli->u_uuid);
            dprintf(s->l_cli->fd, "LOGOUT REAL\n");
        }
    }
}