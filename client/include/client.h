/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** client
*/

#ifndef CLIENT_H_
#define CLIENT_H_

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
#include <uuid/uuid.h>
#include <signal.h>

#include "logging_server.h"
#include "logging_client.h"

typedef enum logged
{
    YES = 1,
    NO = 0
} logged_t;

typedef struct client_s
{
    int sockid;
    char *u_uuid;
    char *name;
    logged_t log_status;
} client_t;

char *get_next_line(int fd);
char **str_warray(char const *str, char f);
char *message_convert(char **str, int start);
int count_parser(char *str);

void rec_login(client_t *cli, char **arr);
void send_login(client_t *cli, char **arr);

void rec_logout(client_t *cli, char **arr);
void send_logout(client_t *cli, char **arr);

void rec_send(client_t *cli, char **arr);
void send_send(client_t *cli, char **arr);

void rec_msg(client_t *cli, char **arr);
void send_msg(client_t *cli, char **arr);

void rec_user(client_t *cli, char **arr);
void send_user(client_t *cli, char **arr);

void rec_users(client_t *cli, char **arr);
void send_users(client_t *cli, char **arr);

void rec_create(client_t *cli, char **arr);
void send_create(client_t *cli, char **arr);

void send_use(client_t *cli, char **arr);
void rec_use(client_t *c, char **a);


void rec_list(client_t *cli, char **arr);
void send_list(client_t *cli, char **arr);
typedef void(*commands)(client_t *cli, char **command);
#endif /* !CLIENT_H_ */
