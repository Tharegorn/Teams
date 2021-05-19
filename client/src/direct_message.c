/*
** EPITECH PROJECT, 2021
** client
** File description:
** direct_message
*/

#include "client.h"

void rec_send(__attribute__((unused)) client_t *cli, char **arr)
{
    if (strcmp(arr[1], "NULL") == 0)
        client_error_unknown_user(arr[2]);
    else
        client_event_private_message_received(arr[1], message_convert(arr, 2));
}

void send_send(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else if (arr[1] == NULL || arr[2] == NULL)
        printf("Invalid Command : /send <user_uuid> <message_body>\n");
    else
        dprintf(cli->sockid, "PM \"%s\" \"%s\"\n", arr[1], arr[2]);
}