/*
** EPITECH PROJECT, 2021
** client
** File description:
** logout
*/

#include "client.h"

void rec_logout(client_t *cli, __attribute__((unused)) char **arr)
{
    if (cli->log_status == YES)
        client_event_logged_out(cli->user_uuid, cli->name);
    exit(0);
}

void send_logout(client_t *cli, __attribute__((unused)) char **arr)
{
    if (cli->log_status == YES)
        client_event_logged_out(cli->user_uuid, cli->name);
    dprintf(cli->sockid, "LOGOUT\n");
    exit(0);
}