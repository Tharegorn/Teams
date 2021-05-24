/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** list
*/

#include "client.h"

void rec_list(__attribute__((unused))client_t *cli, char **arr)
{
    if (strcmp(arr[1], "TEAM") == 0)
        client_print_teams(arr[2], arr[3], arr[4]);
    if (strcmp(arr[1], "CHAN") == 0)
        client_team_print_channels(arr[2], arr[3], arr[4]);
    if (strcmp(arr[1], "TH") == 0)
        client_channel_print_threads(arr[2], arr[3], (time_t)atoi(arr[4]), arr[5], arr[6]);
    if (strcmp(arr[1], "REP") == 0)
        client_thread_print_replies(arr[2], arr[3], (time_t)atoi(arr[4]), arr[5]);
    if (strcmp(arr[1], "ERROR") == 0)
        client_error_already_exist();
}

void send_list(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else if (arr[1] == 0)
        dprintf(cli->sockid, "LIST\n");
    else
        client_error_unauthorized();
}
