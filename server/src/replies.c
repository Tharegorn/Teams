/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** replies
*/

#include "server.h"

void contact_on_reply(server_t *s, char *body, time_t t)
{
    FILE *fd;
    char *line = NULL;
    size_t size = 0;
    char **array = NULL;
    int pos = s->l_cli->position;
    char *uu = s->l_cli->u_uuid;
    char *th = s->l_cli->teams->thread;
    char *te = s->l_cli->teams->teams;

    chdir("./server/logs/teams/");
    chdir(s->l_cli->teams->teams);
    fd = fopen("subscribe", "r+");
    while (getline(&line, &size, fd) != -1) {
        array = str_warray(line, ' ');
        go_prev(s);
        for(; s->l_cli->next != NULL; s->l_cli = s->l_cli->next) {
            if (strcmp(array[1], s->l_cli->u_uuid) == 0 && s->l_cli->position == pos) {
                dprintf(s->l_cli->fd, "CREATE PRINT REP \"%s\" \"%s\" \"%ld\" \"%s\"\n",
                th, uu, t, body);
            } else if (strcmp(array[1], s->l_cli->u_uuid) == 0) {
                dprintf(s->l_cli->fd, "CREATE EVENT REP \"%s\" \"%s\" \"%s\" \"%s\"\n",
                te, th, uu, body);
            }
        }
        go_prev(s);
    }
    free(line);
    fclose(fd);
    chdir("../../../../");
}
void add_reply(server_t *s, char *body)
{
    FILE *fd;
    char *t = s->l_cli->teams->teams;
    char *th = s->l_cli->teams->thread;
    char *uu = s->l_cli->u_uuid;
    time_t timed = time(NULL);

    chdir("./server/logs/teams/");
    chdir(t);
    chdir(s->l_cli->teams->channel);
    chdir(s->l_cli->teams->thread);
    fd = fopen("replies", "a");
    fprintf(fd, "\"%s\" \"%s\" \"%ld\" \"%s\"\n", th, uu, timed, body);
    server_event_reply_created(th, uu, body);
    chdir("../../../../../../");
    fclose(fd);
    contact_on_reply(s, body, timed);
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
