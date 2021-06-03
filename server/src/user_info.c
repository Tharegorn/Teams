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

void user_info_two(server_t *s, char **arr, int exists, char *request)
{
    int online = 0;
    int fd_client = s->l_cli->fd;
    int stk = s->l_cli->position;

    if (exists == 0)
        dprintf(fd_client, "USER NULL \"%s\"\n", request);
    else {
        go_prev(s);
        for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next)
            if (s->l_cli->u_uuid != NULL &&
            strcmp(s->l_cli->u_uuid, arr[1]) == 0)
                online = 1;
        go_prev(s);
        for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next)
            if (s->l_cli->position == stk)
                break;
        dprintf(fd_client, "USER \"%s\" \"%s\" %d\n", arr[0], arr[1], online);
    }
}
void user_info(server_t *s, char **array)
{
    size_t size = 0;
    char *line;
    char **arr = NULL;
    int exists = 0;
    FILE *fd;

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
    user_info_two(s, arr, exists, array[1]);
    info_free(fd, line, arr);
}
