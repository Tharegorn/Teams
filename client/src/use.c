/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** use
*/

#include "client.h"

void rec_use(__attribute__((unused))client_t *c, __attribute((unused))char **a)
{
}

void second_use(int id, char **arr)
{
    dprintf(id, "USE ");
    for (int i = 1; arr[i]; i++) {
        if (arr[i + 1] == NULL)
           dprintf(id, "%s", arr[i]);
        else
           dprintf(id, "%s ", arr[i]);
    }
    dprintf(id, "\n");
}

void send_use(client_t *cli, char **arr)
{
    if (cli->log_status == NO)
        client_error_unauthorized();
    else {
        if (arr[1] == NULL)
            dprintf(cli->sockid, "USE\n");
        else {
            second_use(cli->sockid, arr);
        }
    }
}