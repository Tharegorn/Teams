/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** main
*/

#include "server.h"

int run = 1;

void sig_handler(int signal)
{
    run = 0;
}

void set_clients(server_t *s)
{
    load_users();
    s->list_clients = malloc(sizeof(client_t));
    s->list_clients->prev = NULL;
    for (int i = 0; i < 30; i++, s->list_clients = s->list_clients->next) {
        s->list_clients->fd = 0;
        s->list_clients->log_status = NO;
        s->list_clients->next = malloc(sizeof(client_t));
        s->list_clients->next->next = NULL;
        s->list_clients->next->prev = s->list_clients;
        s->list_clients->position = i;
    }
    go_prev(s);
}
void init_server(server_t *s)
{
    fd_set write_fd;
    fd_set read_fd;
    int tmp = s->sockid;
    int nw_socket;
    struct sockaddr_in adr;
    socklen_t ads = sizeof(adr);

    set_clients(s);
    signal(SIGINT, sig_handler);
    while (run == 1) {
        get_maxfd(s, &tmp, &read_fd, &write_fd);
        if (select(tmp + 1, &read_fd, &write_fd, NULL, 0x0) < 0)
            break;
        if (FD_ISSET(s->sockid, &read_fd)) {
            if ((nw_socket = accept(s->sockid,\
             (struct sockaddr *)&adr, &ads)) < 0)
                break;
            set_socketclient(s, &nw_socket);
        }
        handle_input(s, &read_fd, &write_fd);
    }
    go_prev(s);
    for (; s->list_clients->next != NULL; s->list_clients = s->list_clients->next) {
        if (s->list_clients->fd != 0) {
            if (s->list_clients->log_status == YES)
                server_event_user_logged_out(s->list_clients->user_uuid);
            dprintf(s->list_clients->fd, "LOGOUT\n");
        }
    }
}

int create_server(server_t *s, int port)
{
    if ((s->sockid = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return -1;
    s->port = port;
    s->serv.sin_family = AF_INET;
    s->serv.sin_port = htons(s->port);
    s->serv.sin_addr.s_addr = INADDR_ANY;
    s->size = sizeof(s->serv);
    s->cli_max = 42;
    s->nb_cli = 0;
    return 0;
}

int serv_handling(server_t *serv)
{
    if (bind(serv->sockid, (struct sockaddr *)&serv->serv, serv->size) == -1) {
        shutdown(serv->sockid, SHUT_RDWR);
        close(serv->sockid);
        return 84;
    }
    if (listen(serv->sockid, 42) < 0) {
        close(serv->sockid);
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    server_t *s;

    if (ac != 2) {
        printf("Usage: ./myteams_server [port]\n");
        return 84;
    }
    s = malloc(sizeof(server_t));
    if (create_server(s, atoi(av[1])) == -1) {
        free(s);
        return 84;
    }
    if (serv_handling(s) == 84)
        return 84;
    init_server(s);
    return 0;
}
