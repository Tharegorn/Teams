/*
** EPITECH PROJECT, 2021
** client
** File description:
** create
*/

#include "client.h"

void rec_create(__attribute__((unused))client_t *cli, char **arr)
{
    if (strcmp(arr[1], "TEAM") == 0 && strcmp(arr[2], "NULL") == 0) {
        client_error_unknown_team(arr[3]);
    }
    else if (strcmp(arr[1], "TEAM") == 0)
        client_event_team_created(arr[2], arr[3], arr[4]);
}

void send_create(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "CREATE \"%s\" \"%s\"\n", arr[1], arr[2]);
}
