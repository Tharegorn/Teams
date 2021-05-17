/*
** EPITECH PROJECT, 2021
** client
** File description:
** user
*/

#include "client.h"

void rec_user(__attribute__((unused)) client_t *cli, char **arr)
{
    if (strcmp(arr[1], "NULL") == 0)
        client_error_unknown_user(arr[2]);
    else
        client_print_user(arr[2], arr[1], atoi(arr[3]));
}

void send_user(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else if (arr[1] == NULL)
        printf("INVALID UUID\n");
    else
        dprintf(cli->sockid, "USER %s\n", arr[1]);
}
