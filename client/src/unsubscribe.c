/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** unsubscribe
*/

#include "client.h"

void rec_unsub(__attribute__((unused))client_t *cli, char **arr)
{
    client_print_unsubscribed(arr[1], arr[2]);
}

void send_unsub(client_t *cli, char **arr)
{
    if (arr[1] == NULL || arr[2] != NULL)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "UNSUB \"%s\"\n", arr[1]);
}
