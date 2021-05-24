/*
** EPITECH PROJECT, 2021
** client
** File description:
** create
*/

#include "client.h"

void rec_create(__attribute__((unused))client_t *cli, char **arr)
{
    if (strcmp(arr[1], "TEAM") == 0 && strcmp(arr[2], "UNKNOW") == 0)
        client_error_unknown_team(arr[3]);
    else if (strcmp(arr[1], "TEAM") == 0)
        client_event_team_created(arr[2], arr[3], arr[4]);
    if (strcmp(arr[1], "CHAN") == 0 && strcmp(arr[2], "UNKNOW") == 0)
        client_error_unknown_channel(arr[3]);
    else if (strcmp(arr[1], "CHAN") == 0)
        client_event_channel_created(arr[2], arr[3], arr[4]);
    if (strcmp(arr[1], "THREAD") == 0 && strcmp(arr[2], "UNKNOW") == 0)
        client_error_unknown_thread(arr[3]);
    else if (strcmp(arr[1], "THREAD") == 0)
        client_event_thread_created(arr[2], arr[3], (time_t)atoi(arr[4]),
        arr[5], arr[6]);
    if (strcmp(arr[1], "REP") == 0)
        client_event_thread_reply_received(arr[2], arr[3], arr[4], arr[5]);
    if (strcmp(arr[1], "ERROR") == 0)
        client_error_already_exist();
}

void send_create(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "CREATE \"%s\" \"%s\"\n", arr[1], arr[2]);
}