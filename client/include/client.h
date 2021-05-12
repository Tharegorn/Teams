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
    char *user_uuid;
    char *name;
    logged_t log_status;
} client_t;

char *get_next_line(int fd);
char **str_warray(char const *str, char f);
#endif /* !CLIENT_H_ */
