/*
** EPITECH PROJECT, 2021
** client
** File description:
** login
*/

#include "client.h"

void rec_login(client_t *cli, char **arr)
{
    if (strcmp(arr[1], "CREATE") == 0) {
        cli->name = strdup(arr[3]);
        cli->u_uuid = strdup(arr[2]);
        cli->log_status = YES;
        client_event_logged_in(cli->u_uuid, cli->name);
    } else
        client_event_logged_in(arr[2], arr[3]);
}

void send_login(client_t *cli, char **arr)
{
    char c = 34;

    if (cli->log_status == YES)
        client_error_already_exist();
    else
    {
        if (arr[1] == NULL)
            client_error_unauthorized();
        else
            dprintf(cli->sockid, "LOGIN %c%s%c\n", c, arr[1], c);
    }
}
