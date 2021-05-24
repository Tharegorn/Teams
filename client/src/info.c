/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** info
*/

#include "client.h"

void rec_info(__attribute__((unused))client_t *c, char **a)
{
    if (strcmp(a[1], "TEAM") == 0)
        client_print_team(a[2], a[3], a[4]);
    if (strcmp(a[1], "CHAN") == 0)
        client_print_channel(a[2], a[3], a[4]);
    if (strcmp(a[1], "TH") == 0)
        client_print_thread(a[2], a[3], (time_t)atoi(a[4]), a[5], a[6]);
}

void send_info(client_t *c, char **a)
{
    if (c->log_status == NO)
        client_error_unauthorized();
    else if (a[1] != NULL)
        client_error_unauthorized();
    else
        dprintf(c->sockid, "INFO\n");
}