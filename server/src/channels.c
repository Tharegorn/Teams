/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** channels
*/

#include "server.h"

int channel_exists(char *name, char *chan_name)
{
    char *line = NULL;
    char **arr = NULL;
    size_t size = 0;
    FILE *fd;

    chdir("./server/logs/teams/");
    chdir(name);
    fd = fopen("list_chans", "r+");
    chdir("../../../../");
    while (getline(&line, &size, fd) != -1) {
        arr = str_warray(line, ' ');
        if (strcmp(arr[0], chan_name) == 0) {
            free(line);
            fclose(fd);
            return 0;
        }
    }
    free(line);
    fclose(fd);
    return 1;
}

void add_channel(char *chan_uuid, char **arr, char *team_uuid)
{
    struct stat st = {0};
    FILE *fd;
    FILE *list = NULL;

    chdir("./server/logs/teams/");
    chdir(team_uuid);
    fd = fopen("list_chans", "a");
    fprintf(fd, "\"%s\" \"%s\" \"%s\"\n", arr[1], chan_uuid, arr[2]);
    if (stat(chan_uuid, &st) == -1) {
        mkdir(chan_uuid, 0700);
        chdir(chan_uuid);
        list = fopen("list_threads", "w");
        chdir("../../../../../");
        fclose(list);
    }
    server_event_channel_created(team_uuid, chan_uuid, arr[1]);
    fclose(fd);
}

void free_chan(char *line, FILE *fd)
{
    chdir("../../../../");
    free(line);
    fclose(fd);
}

void contact_all_chan(server_t *s, char **arr, char *uuid)
{
    FILE *fd;
    char *line = NULL;
    size_t size = 0;
    char **array = NULL;
    int pos = s->l_cli->position;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    fd = fopen("subscribe", "r+");
    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        go_prev(s);
        for(; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
            if (strcmp(array[1], s->l_cli->u_uuid) == 0 && s->l_cli->position == pos) {
                dprintf(s->l_cli->fd, "LIST CHAN \"%s\" \"%s\" \"%s\"\n",
                uuid, arr[1], arr[2]);
            } else if (strcmp(array[1], s->l_cli->u_uuid) == 0) {
                dprintf(s->l_cli->fd, "CREATE CHAN \"%s\" \"%s\" \"%s\"\n",
                uuid, arr[1], arr[2]);
            }
        }
        go_prev(s);
    }
    free_chan(line, fd);
}

void create_channel(server_t *s, char **arr)
{
    char *uuid = gen_uuid();
    int pos = s->l_cli->position;

    if (subed(s, s->l_cli->teams->teams) == 0) {
        dprintf(s->l_cli->fd, "SUB UNAUTH\n");
        return;
    }
    if (strlen(arr[1]) <= 32 && strlen(arr[2]) <= 255 &&\
     channel_exists(s->l_cli->teams->teams, arr[1]) == 1) {
        add_channel(uuid, arr, s->l_cli->teams->teams);
        contact_all_chan(s, arr, uuid);
        for (; s->l_cli->next != NULL; s->l_cli = s->l_cli->next)
            if (s->l_cli->position == pos)
                break;
    } else
        dprintf(s->l_cli->fd, "CREATE ERROR\n");
    free(uuid);
}
