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

void add_thread(server_t *s, char *ti, char *b, char *u)
{
    FILE *fd;
    char *line = NULL;
    char **array = NULL;
    size_t size = 0;
    time_t t = fill_file(s, ti, b, u);
    int pos = s->l_cli->position;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    fd = fopen("subscribe", "r+");
    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        go_prev(s);
        for(; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
            if (s->l_cli->log_status == YES && strcmp(array[1], s->l_cli->u_uuid) == 0 && s->l_cli->position == pos) {
                dprintf(s->l_cli->fd,
                "CREATE PRINT THREAD \"%s\" \"%s\" \"%ld\" \"%s\" \"%s\"\n",
                u, s->l_cli->u_uuid, t, ti, b);
            } else if (s->l_cli->log_status == YES && strcmp(array[1], s->l_cli->u_uuid) == 0) {
                dprintf(s->l_cli->fd,
                "CREATE EVENT THREAD \"%s\" \"%s\" \"%ld\" \"%s\" \"%s\"\n",
                u, s->l_cli->u_uuid, t, ti, b);
            }
        }
    }
    go_prev(s);
    free(line);
    fclose(fd);
    chdir("../../../../");
}

void create_thread(server_t *s, char **arr)
{
    char *uuid = gen_uuid();

    if (subed(s, s->l_cli->teams->teams) == 0) {
        dprintf(s->l_cli->fd, "SUB UNAUTH\n");
        return;
    }
    if (strlen(arr[1]) <= 32 && strlen(arr[2]) <= 512 &&
    thread_exists(s->l_cli->teams->teams,
    s->l_cli->teams->channel, arr[1]) == 1) {
        add_thread(s, arr[1], arr[2], uuid);
    } else
        dprintf(s->l_cli->fd, "CREATE ERROR\n");
    free(uuid);
}
