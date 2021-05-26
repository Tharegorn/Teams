/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** subscribe
*/

#include "client.h"

void rec_sub(client_t *cli, char **arr)
{
    client_print_subscribed(cli->u_uuid, arr[1]);
}

void send_sub(client_t *cli, char **arr)
{
    if (arr[1] == NULL || arr[2] != NULL)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "SUB \"%s\"\n", arr[1]);
}
