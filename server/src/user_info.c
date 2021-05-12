/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** user_info
*/

#include "server.h"

void info_free(FILE *fd, char *line, char **arr)
{
    fclose(fd);
    free(line);
    for (int i = 0; arr[i]; i++, free(arr[i]));
}

void user_info_two(server_t *s, char **arr, int exists, int stk)
{
    int online = 0;
    int fd_client = s->list_clients->fd;

    if (exists == 0) {
        dprintf(fd_client, "USER NULL %s\n", arr[1]);
    } else {
        go_prev(s);
        for (; s->list_clients->next != NULL;\
         s->list_clients = s->list_clients->next) {
            if (strcmp(s->list_clients->user_uuid, arr[1]) == 0)
                online = 1;
        }
        go_prev(s);
        for (; s->list_clients->next != NULL;\
        s->list_clients = s->list_clients->next) {
            if (s->list_clients->position == stk)
                break;
        }
        dprintf(fd_client, "USER %s %s %d\n", arr[0], arr[1], online);
    }
    
}
void user_info(server_t *s, char **array)
{
    size_t size = 0;
    char *line;
    char **arr = NULL;
    int exists = 0;
    FILE *fd;
    int stk = s->list_clients->position;

    if (array[1] == NULL)
        return;
    fd = fopen("./server/logs/user_uuid.log", "r");
    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[1], array[1]) == 0) {
            exists = 1;
            break;
        }
    }
    user_info_two(s, arr, exists, stk);
    info_free(fd, line, arr);
}