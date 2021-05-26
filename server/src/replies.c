/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** replies
*/

#include "server.h"

void add_reply(server_t *s, char *body)
{
    FILE *fd;
    char *t = s->l_cli->teams->teams;
    char *th = s->l_cli->teams->thread;
    char *uu = s->l_cli->u_uuid;

    chdir("./server/logs/teams/");
    chdir(t);
    chdir(s->l_cli->teams->channel);
    chdir(s->l_cli->teams->thread);
    fd = fopen("replies", "a");
    fprintf(fd, "\"%s\" \"%s\" \"%ld\" \"%s\"\n", th, uu, time(NULL), body);
    server_event_reply_created(th, uu, body);
    dprintf(s->l_cli->fd, "CREATE REP \"%s\" \"%s\" \"%s\" \"%s\"\n",
    t, th, uu, body);
    chdir("../../../../../../");
    fclose(fd);
}

void create_reply(server_t *s, char **arr)
{
    if (subed(s, s->l_cli->teams->teams) == 0) {
        dprintf(s->l_cli->fd, "SUB UNAUTH\n");
        return;
    }
    if (strlen(arr[1]) <= 512)
        add_reply(s, arr[1]);
    else
        dprintf(s->l_cli->fd, "CREATE ERROR\n");
}
