/*
** EPITECH PROJECT, 2021
** client
** File description:
** messages
*/

#include "client.h"

void rec_msg(__attribute__((unused)) client_t *cli, char **arr)
{
    if (strcmp(arr[1], "NULL") == 0)
        client_error_unknown_user(arr[2]);
    else if (strcmp(arr[1], "ANY") == 0)
        printf("No pm with this User\n");
    else
        client_private_message_print_messages(arr[1], (time_t)atoi(arr[2]),\
         message_convert(arr, 3));
}

void send_msg(client_t *cli, char **arr)
{
    if (arr[1] == NULL || cli->log_status == NO)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "MSG %s\n", arr[1]);
}