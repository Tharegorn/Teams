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
#include <uuid/uuid.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>

#include "logging_server.h"
#include "logging_client.h"

typedef enum logged
{
    YES = 1,
    NO = 0
} logged_t;

typedef enum context
{
    ANY = 0,
    TEAM = 1,
    CHANNEL = 2,
    THREAD = 3

} context_t;

typedef struct teams_s
{
    char *teams;
    char *channel;
    char *thread;
} teams_t;

typedef struct client_s client_t;

typedef struct client_s
{
    int fd;
    char *u_uuid;
    char *name;
    int position;
    teams_t *teams;
    context_t contex;
    logged_t log_status;
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
    client_t *l_cli;
} server_t;

char *get_next_line(int fd);
char **str_warray(char const *str, char f);
void get_maxfd(server_t *s, int *tmp, fd_set *read_fd, fd_set *write_fd);
void go_prev(server_t *s);
void direct_message(server_t *s, char **arr);
void set_socketclient(server_t *s, int *socket);
void handle_input(server_t *s, fd_set *read_fd, fd_set *write_fd);
void user_info(server_t *s, char **array);
void logout(server_t *s, char **arr);
void load_users(void);
void add_user(server_t *s, char **arr);
char *gen_uuid(void);
void info_free(FILE *fd, char *line, char **arr);
client_t *create_client(int fd);
void go_prev(server_t *s);
void retreive_message(server_t *s, char **arr);
void users(server_t *s, char **arr);
void set_clients(server_t *s);
void create(server_t *s, char **arr);
void create_team(server_t *s, char **arr);
void create_channel(server_t *s, char **arr);
void use(server_t *s, char **arr);
void create_thread(server_t *s, char **arr);
void create_reply(server_t *s, char **arr);
int check_params(server_t *s);
void list(server_t *s, char **array);
void info(server_t *s, char **arr);
void go_pos(int pos, server_t *s);
int team_exists(char *uuid);
int is_online(server_t *s, char *uuid);
void sub(server_t *s, char **arr);
typedef void (*commands)(server_t *s, char **command);
#endif /* !SERVER_H_ */
