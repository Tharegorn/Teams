/*
** EPITECH PROJECT, 2021
** client
** File description:
** logout
*/

#include "client.h"

void rec_logout(client_t *cli, char **arr)
{
    if (strcmp(arr[1], "REAL") == 0) {
        if (cli->log_status == YES)
            client_event_logged_out(cli->u_uuid, cli->name);
        exit(0);
    } else if (strcmp(arr[1], "DISPLAY") == 0)
        client_event_logged_out(arr[2], arr[3]);
}

void send_logout(client_t *cli, __attribute__((unused)) char **arr)
{
    if (cli->log_status == YES)
        client_event_logged_out(cli->u_uuid, cli->name);
    dprintf(cli->sockid, "LOGOUT\n");
    exit(0);
}
