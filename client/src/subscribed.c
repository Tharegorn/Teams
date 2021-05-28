/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** subscribed
*/

#include "client.h"

void send_subscribed(client_t *cli, char **arr)
{
    if (arr[2] != NULL || cli->log_status == NO)
        client_error_unauthorized();
    else {
        if (arr[1] == NULL)
            dprintf(cli->sockid, "SUBED\n");
        else
            dprintf(cli->sockid, "SUBED %s\n", arr[1]);
    }
}
