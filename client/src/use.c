/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** use
*/

#include "client.h"

void send_use(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else {
        if (arr[1] == NULL)
            dprintf(cli->sockid, "USE\n");
        else if (arr[2] == NULL)
            dprintf(cli->sockid, "USE %s\n", arr[1]);
    }
}
