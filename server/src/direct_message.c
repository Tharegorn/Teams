/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** direct_message
*/

#include "server.h"

void save_message(char **arr, char *sender_uuid)
{
    FILE *fd;
    char file[5000];

    strcpy(file, "./server/logs/PM/");
    strcat(file, arr[1]);
    strcat(file, ".log");
    if(access(file, F_OK ) != 0 )
        fd = fopen(file, "w");
    else
        fd = fopen(file, "a");
    fprintf(fd, "%s %ld ",sender_uuid, time(NULL));
    for (int i = 2; arr[i]; i++)
        fprintf(fd, "%s ",arr[i]);
    fputs("\n", fd);
    fclose(fd);
}

void send_message(server_t *s, char **arr)
{
    int stk = s->list_clients->position;
    char *name = strdup(s->list_clients->user_uuid);

    go_prev(s);
    for (; s->list_clients->next != NULL;\
     s->list_clients = s->list_clients->next) {
        if (strcmp(s->list_clients->user_uuid, arr[1]) == 0) {
            save_message(arr, name);
            dprintf(s->list_clients->fd, "PM %s ", name);
            for (int i = 2; arr[i]; i++)
                dprintf(s->list_clients->fd, "%s ", arr[i]);
            dprintf(s->list_clients->fd, "\n");
        }
    }
    go_prev(s);
    for (; s->list_clients->next != NULL;\
    s->list_clients = s->list_clients->next) {
        if (s->list_clients->position == stk)
            break;
    }
    free(name);
}

void direct_message(server_t *s, char **arr)
{

    char **array;
    char *line;
    size_t size = 0;
    FILE *fd;
    int exists = 0;

    if (arr[1] == NULL || arr[2] == NULL)
        return;
    fd = fopen("./server/logs/user_uuid.log", "r");
    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        if (strcmp(array[1], arr[1]) == 0) {
            send_message(s, arr);
            exists = 1;
        }
    }
    if (exists == 0) {
        dprintf(s->list_clients->fd, "PM NULL %s\n", arr[1]);
    }
}