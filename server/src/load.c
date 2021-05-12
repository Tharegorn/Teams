/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** load
*/

#include "server.h"

void load_users(void)
{
    char *line;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd = fopen("./server/logs/user_uuid.log", "r");

    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        server_event_user_loaded(arr[1], arr[0]);
    }
    fclose(fd);
    free(line);
    if (arr != NULL)
        for (int i = 0; arr[i]; i++, free(arr[i]));
}