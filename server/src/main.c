/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** main
*/

#include "server.h"

client_t *create_client(int fd)
{
    client_t *client = malloc(sizeof(client_t));

    client->fd = fd;
    return client;
}

void set_clients(server_t *s)
{
    for (int i = 0; s->clients[i]; i++)
        s->clients[i] = 0;
}
void init_server(server_t *s)
{
    fd_set write_fd;
    fd_set read_fd;
    set_clients(s);
    int tmp = s->sockid;
    int nw_socket;
    struct sockaddr_in adr;
    socklen_t ads = sizeof(adr);
    FD_ZERO(&write_fd);
    FD_ZERO(&read_fd);
    FD_SET(s->sockid, &write_fd);
    FD_SET(s->sockid, &read_fd);
    char *str;
    while (1) {
        for (int i = 0; i < 30; i++) {
            if (s->clients[i] > 0)
                FD_SET(s->clients[i], &read_fd);
            if (s->clients[i] > tmp)
                tmp = s->clients[i];
        }
        if (select(tmp + 1, &read_fd, &write_fd, NULL, 0x0) < 0)
            break;
        if (FD_ISSET(s->sockid, &read_fd)) {
            if ((nw_socket = accept(s->sockid, (struct sockaddr *)&adr, &ads)) < 0)
                break;
            printf("New Connection !\n");
            dprintf(nw_socket, "200 Connecté\n");
            for (int i = 0; i < 30; i++) {
                if (s->clients[i] == 0) {
                    s->clients[i] = nw_socket;
                    printf("Change socket nb %d\n", i);
                    break;
                }
            }

        }
        for (int i = 0; i < 30; i++) {
            if (FD_ISSET( s->clients[i], &read_fd)) {
                if ((str = get_next_line(s->clients[i])) != NULL) {
                    getpeername(s->clients[i] , (struct sockaddr*)&adr , &ads);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(adr.sin_addr) , ntohs(adr.sin_port));
                    close(s->clients[i]);
                    s->clients[i] = 0;
                    FD_CLR(s->clients[i], &read_fd);
                    FD_CLR(s->clients[i], &write_fd);
                } else {
                    dprintf(s->clients[i], "200 Reçu : %s\n", str);
                }
            }
        }
        str = NULL;
        FD_ZERO(&read_fd);
        FD_ZERO(&write_fd);
        FD_SET(s->sockid, &read_fd);
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
    if (bind(serv->sockid, (struct sockaddr *)&serv->serv, serv->size) == -1)
    {
        shutdown(serv->sockid, SHUT_RDWR);
        close(serv->sockid);
        return 84;
    }
    if (listen(serv->sockid, 42) < 0)
    {
        close(serv->sockid);
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    server_t *s;

    if (ac != 2)
    {
        printf("Usage: ./myteams_server [port]\n");
        return 84;
    }
    s = malloc(sizeof(server_t));
    if (create_server(s, atoi(av[1])) == -1)
    {
        free(s);
        return 84;
    }
    if (serv_handling(s) == 84)
        return 84;
    init_server(s);
}
