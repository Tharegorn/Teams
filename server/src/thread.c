/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** thread
*/

#include "server.h"

int thread_exists(char *team, char *chan, char *cmp)
{
    FILE *fd;
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;

    chdir("./server/logs/teams/");
    chdir(team);
    chdir(chan);
    fd = fopen("list_threads", "r+");
    chdir("../../../../../");
    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[0], cmp) == 0) {
            free(line);
            fclose(fd);
            return 0;
        }
    }
    free(line);
    fclose(fd);
    return 1;
}

time_t fill_file(server_t *s, char *title, char *body, char *uuid)
{
    FILE *fd;
    FILE *file;
    time_t now = time(NULL);

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    chdir(s->l_cli->teams->channel);
    fd = fopen("list_threads", "a");
    fprintf(fd, "\"%s\" \"%s\" \"%s\" \"%ld\" \"%s\"\n",
    title, uuid, body, now, s->l_cli->u_uuid);
    mkdir(uuid, 0700);
    chdir(uuid);
    file = fopen("replies", "w+");
    fclose(file);
    fclose(fd);
    server_event_thread_created(s->l_cli->teams->channel, uuid,
    s->l_cli->u_uuid, title, body);
    chdir("../../../../../../");
    return now;
}

void add_thread(server_t *s, char *title, char *body, char *uuid)
{
    time_t t = fill_file(s, title, body, uuid);

    dprintf(s->l_cli->fd,
    "CREATE THREAD \"%s\" \"%s\" \"%ld\" \"%s\" \"%s\"\n",
    uuid, s->l_cli->u_uuid, t, title, body);
}


void create_thread(server_t *s, char **arr)
{
    char *uuid = gen_uuid();

    if (strlen(arr[1]) <= 32 && strlen(arr[2]) <= 512 &&
    thread_exists(s->l_cli->teams->teams,
    s->l_cli->teams->channel, arr[1]) == 1) {
        add_thread(s, arr[1], arr[2], uuid);
    } else
        dprintf(s->l_cli->fd, "CREATE ERROR\n");
    free(uuid);
}
