/*
** EPITECH PROJECT, 2021
** my_teams [WSL: Ubuntu]
** File description:
** retreive_message
*/

#include "server.h"

char *c(char **str, int start)
{
    char *tmp = NULL;
    int size = 0;
    int words = 0;

    if (str[3] == NULL)
        return str[2];
    for (int i = start; str[i]; i++, words++)
        size += strlen(str[i]);
    tmp = malloc(sizeof (char) * (size + words + 1));
    tmp[0] = '\0';
    for (int i = start; str[i]; i++) {
        tmp = strcat(tmp, str[i]);
        tmp = strcat(tmp, " ");
    }
    tmp[size + words] = '\0';
    tmp = strdup(tmp);
    return tmp;
}

int get_path(server_t *s, char *file)
{
    strcpy(file, "./server/logs/PM/");
    strcat(file, s->l_cli->u_uuid);
    strcat(file, ".log");
    if (access(file, F_OK) != 0) {
        dprintf(s->l_cli->fd, "MSG ANY\n");
        return 1;
    }
    return 0;
}

void free_all(int any, char *line, FILE *fd, char **a)
{
    if (any != 1)
        dprintf(any, "MSG ANY\n");
    free(line);
    for (int i = 0; a[i]; i++)
        free(a[i]);
    fclose(fd);
}

void retreive(server_t *s, char *uuid)
{
    FILE *fd;
    char file[5000];
    char *line = NULL;
    char **a = NULL;
    size_t size = 0;
    int any =  s->l_cli->fd;

    if (get_path(s, file) == 1)
        return;
    fd = fopen(file, "r+");
    while(getline(&line, &size, fd) != -1) {
        a = str_warray(line, ' ');
        if (strcmp(a[0], uuid) == 0) {
            dprintf(s->l_cli->fd, "MSG \"%s\" \"%s\" \"%s\"\n",\
             a[0], a[1], a[2]);
            usleep(0.1);
            any = 1;
        }
    }
    free_all(any, line, fd, a);
}

void retreive_message(server_t *s, char **arr)
{
    char *line = NULL;
    char **a = NULL;
    size_t size = 0;
    int exists = 0;
    FILE *fd = fopen("./server/logs/user_uuid.log", "r+");

    while (getline(&line, &size, fd) != -1) {
        a = str_warray(line, ' ');
        if (strcmp(arr[1], a[1]) == 0) {
            retreive(s, arr[1]);
            exists = 1;
            break;
        }
    }
    if (exists == 0)
        dprintf(s->l_cli->fd, "MSG NULL %s\n", arr[1]);
    free(line);
    fclose(fd);
}
