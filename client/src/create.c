/*
** EPITECH PROJECT, 2021
** client
** File description:
** create
*/

#include "client.h"

void rec_create(__attribute__((unused))client_t *cli, char **arr)
{
    for (int i = 0; arr[i]; i++)
        printf("%s", arr[i]);
    printf("\n");
}

void send_create(client_t *cli, char **arr)
{
    char c = 34;

    if (cli->log_status == NO)
        client_error_unauthorized();
    else
        dprintf(cli->sockid, "CREATE %c%s%c %c%s%c\n", c, arr[1], c, c, arr[2], c);
}