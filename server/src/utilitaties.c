/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** utilitaties
*/

#include "server.h"

int get_status(server_t *s, char *uuid, int pos)
{
    int status = 0;

    go_prev(s);
    for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next)
        if (strcmp(s->l_cli->u_uuid, uuid) == 0)
            status = 1;
    go_prev(s);
    for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next)
        if (s->l_cli->position == pos)
            break;
    return status;
}
