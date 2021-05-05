/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <netinet/ip.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef struct client_s client_t;
typedef struct client_s
{
    int fd;
    char *uuid;
    char *name;
    client_t *next;
    client_t *prev;
} client_t;

typedef struct server_s
{
    int sockid;
    int port;
    socklen_t size;
    struct sockaddr_in serv;
    int nb_cli;
    int cli_max;
    struct pollfd *pfds;
    int clients[30];
    client_t *list_clients;
} server_t;

char *get_next_line(int fd);
char **str_warray(char const *str, char f);
void get_maxfd(server_t *s, int *tmp, fd_set *read_fd, fd_set *write_fd);
void go_prev(server_t *s);
void set_socketclient(server_t *s, int *socket);
void handle_input(server_t *s, fd_set *read_fd, fd_set *write_fd);
#endif /* !SERVER_H_ */
