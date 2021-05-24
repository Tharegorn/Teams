/*
** EPITECH PROJECT, 2021
** B-NWP-400-LYN-4-1-myteams-romain.bouguet [WSL: Ubuntu-20.04]
** File description:
** utils
*/
#include "server.h"
#include <uuid/uuid.h>

static commands list_commands[] = {&add_user, &logout, &user_info,\
 &direct_message, &retreive_message, &users, &create, &use, &list};

char *gen_uuid(void)
{
    uuid_t new_uuid;
    char *uuid = malloc(32);

    uuid_generate_random(new_uuid);
    uuid_unparse(new_uuid, uuid);
    return (uuid);
}

void handle_commands(server_t *s, char *str)
{
    char **arr = str_warray(str, ' ');
    char *instruction[] = {"LOGIN", "LOGOUT", "USER", "PM", "MSG",
                             "USERS", "CREATE", "USE", "LIST", NULL};
    if (arr[0] == NULL)
        return;
    for (int i = 0; instruction[i]; i++) {
        if (strcmp(arr[0], instruction[i]) == 0) {
            list_commands[i](s, arr);
            break;
        }
    }
}

void get_maxfd(server_t *s, int *tmp, fd_set *read_fd, fd_set *write_fd)
{
    FD_ZERO(read_fd);
    FD_ZERO(write_fd);
    FD_SET(s->sockid, read_fd);
    FD_SET(s->sockid, write_fd);
    for (; s->l_cli->next != NULL;
         s->l_cli = s->l_cli->next) {
        if (s->l_cli->fd > 0)
            FD_SET(s->l_cli->fd, read_fd);
        if (s->l_cli->fd > *tmp)
            *tmp = s->l_cli->fd;
    }
    go_prev(s);
}

void set_socketclient(server_t *s, int *socket)
{
    for (; s->l_cli->next != NULL;
         s->l_cli = s->l_cli->next) {
        if (s->l_cli->fd == 0) {
            s->l_cli->fd = *socket;
            break;
        }
    }
    go_prev(s);
}

void handle_input(server_t *s, fd_set *read_fd, fd_set *write_fd)
{
    char *str = NULL;

    for (; s->l_cli->next != NULL;
         s->l_cli = s->l_cli->next) {
        if (FD_ISSET(s->l_cli->fd, read_fd)) {
            if ((str = get_next_line(s->l_cli->fd)) == NULL) {
                close(s->l_cli->fd);
                s->l_cli->fd = 0;
                FD_CLR(s->l_cli->fd, read_fd);
                FD_CLR(s->l_cli->fd, write_fd);
            }
            else
                handle_commands(s, str);
        }
    }
    go_prev(s);
    free(str);
}
