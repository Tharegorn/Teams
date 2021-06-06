/*
** EPITECH PROJECT, 2021
** client
** File description:
** create
*/

#include "client.h"

void print_create(char **arr)
{
    if (strcmp(arr[2], "TEAM") == 0 && strcmp(arr[3], "UNKNOW") == 0)
        client_error_unknown_team(arr[4]);
    else if (strcmp(arr[2], "TEAM") == 0)
        client_print_team_created(arr[3], arr[4], arr[5]);
    if (strcmp(arr[2], "CHAN") == 0 && strcmp(arr[3], "UNKNOW") == 0)
        client_error_unknown_channel(arr[4]);
    else if (strcmp(arr[2], "CHAN") == 0)
        client_print_channel_created(arr[3], arr[4], arr[5]);
    if (strcmp(arr[2], "THREAD") == 0 && strcmp(arr[3], "UNKNOW") == 0)
        client_error_unknown_thread(arr[4]);
    else if (strcmp(arr[2], "THREAD") == 0)
        client_print_thread_created(arr[3], arr[4], (time_t) atoi(arr[5]),
                                    arr[6], arr[7]);
    if (strcmp(arr[2], "REP") == 0)
        client_print_reply_created(arr[3], arr[4],
        (time_t) atoi(arr[5]), arr[6]);
    if (strcmp(arr[2], "ERROR") == 0)
        client_error_already_exist();
}

void event_create(char **arr)
{
    if (strcmp(arr[2], "TEAM") == 0)
        client_event_team_created(arr[3], arr[4], arr[5]);
    if (strcmp(arr[2], "CHAN") == 0)
        client_event_channel_created(arr[3], arr[4], arr[5]);
    if (strcmp(arr[2], "THREAD") == 0)
        client_event_thread_created(arr[3], arr[4], (time_t) atoi(arr[5]),
                                    arr[6], arr[7]);
    if (strcmp(arr[2], "REP") == 0)
        client_event_thread_reply_received(arr[3], arr[4], arr[5], arr[6]);
}

void rec_create(__attribute__((unused))client_t *cli, char **arr)
{
    if (strcmp(arr[1], "PRINT") == 0)
        print_create(arr);
    else if (strcmp(arr[1], "EVENT") == 0)
        event_create(arr);
}

void send_create(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "CREATE \"%s\" \"%s\"\n", arr[1], arr[2]);
}