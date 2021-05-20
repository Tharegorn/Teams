/*
** EPITECH PROJECT, 2021
** client
** File description:
** users
*/

#include "client.h"

void rec_users(__attribute__((unused)) client_t *cli, char **arr)
{
    client_print_users(arr[2], arr[1], atoi(arr[3]));
}

void send_users(client_t *cli, __attribute__((unused)) char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "USERS\n");
}