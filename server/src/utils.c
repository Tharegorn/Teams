/*
** EPITECH PROJECT, 2021
** B-NWP-400-LYN-4-1-myteams-romain.bouguet [WSL: Ubuntu-20.04]
** File description:
** utils
*/
#include "server.h"

void get_maxfd(server_t *s, int *tmp, fd_set *read_fd, fd_set *write_fd)
{
    FD_ZERO(read_fd);
    FD_ZERO(write_fd);
    FD_SET(s->sockid, read_fd);
    FD_SET(s->sockid, write_fd);
    for (; s->list_clients->next != NULL; s->list_clients = s->list_clients->next) {
        if (s->list_clients->fd > 0)
            FD_SET(s->list_clients->fd, read_fd);
        if (s->list_clients->fd > *tmp)
            *tmp = s->list_clients->fd;
    }
    go_prev(s);
}

void set_socketclient(server_t *s, int *socket)
{
    for (; s->list_clients->next != NULL; s->list_clients = s->list_clients->next) {
        if (s->list_clients->fd == 0) {
            s->list_clients->fd = *socket;
            break;
        }
    }
    go_prev(s);
}

void handle_input(server_t *s, fd_set *read_fd, fd_set *write_fd)
{
    char *str = NULL;

    for (; s->list_clients->next != NULL; s->list_clients = s->list_clients->next) {
        if (FD_ISSET(s->list_clients->fd, read_fd)) {
            if ((str = get_next_line(s->list_clients->fd)) == NULL) {
                close(s->list_clients->fd);
                s->list_clients->fd = 0;
                FD_CLR(s->list_clients->fd, read_fd);
                FD_CLR(s->list_clients->fd, write_fd);
            } else {
                dprintf(s->list_clients->fd, "200 Reçu : %s\n", str);
            }
        }
    }
    go_prev(s);
    free(str);
}