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

struct pollfd *pfds;
typedef struct client_s
{
    int fd;
    // char *name;
    // char $uuid;
    // struct sockaddr_in add;
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
} server_t;

char *get_next_line(int fd);
char **str_warray(char const *str, char f);
#endif /* !SERVER_H_ */
