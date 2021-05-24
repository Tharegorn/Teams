/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** main
*/

#include "client.h"

static commands rec[] = {&rec_login, &rec_logout, &rec_user,\
 &rec_users, &rec_send, &rec_msg, &rec_create, &rec_use, &rec_list, &rec_info};
static commands to_server[] = {&send_login, &send_logout,\
 &send_user, &send_users, &send_send, &send_msg, &send_create, &send_use, &send_list, &send_info};
int run = 1;

void handle_signal(__attribute__((unused)) int signal)
{
    run = 0;
}

void receive(client_t *cli)
{
    char **arr = NULL;
    char buffer[5024];
    int len = 0;
    char *args[] = {"LOGIN", "LOGOUT", "USER", "USERS", "PM", "MSG", "CREATE", "USE", "LIST", "INFO", NULL};

    if ((len = recv(cli->sockid, buffer, 5024 - 1, 0)) < 0)
        return;
    buffer[len] = 0;
    arr = str_warray(buffer, ' ');
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], arr[0]) == 0) {
            rec[i](cli, arr);
            break;
        }
    }
}

void send_to_server(client_t *cli, char *line)
{
    char **arr = NULL;
    int j = 0;
    char *args[] = {"/login", "/logout",\
     "/user", "/users", "/send", "/messages", "/create", "/use", "/list", "/info", NULL};

    if (strlen(line) == 0) {
        client_error_unauthorized();
        return;
    }
    arr = str_warray(line, ' ');
    if (arr[0] == NULL)
        return;
    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], arr[0]) == 0) {
            to_server[i](cli, arr);
            j = 1;
            break;
        }
    }
    if (j == 0)
        client_error_unauthorized();
}

void loop(client_t *cli)
{
    fd_set rfd;

    signal(SIGINT, handle_signal);
    while (run == 1) {
        FD_ZERO(&rfd);
        FD_SET(STDIN_FILENO, &rfd);
        FD_SET(cli->sockid, &rfd);
        if (select(cli->sockid + 1, &rfd, NULL, NULL, NULL) < 0)
            break;
        if (FD_ISSET(STDIN_FILENO, &rfd))
            send_to_server(cli, get_next_line(0));
        else if (FD_ISSET(cli->sockid, &rfd))
            receive(cli);
    }
    if (cli->log_status == YES)
        client_event_logged_out(cli->u_uuid, cli->name);
    dprintf(cli->sockid, "LOGOUT\n");
    exit(0);
}

int main(int ac, char **av)
{
    if (ac != 3)
        return 84;

    client_t *cli = malloc(sizeof(client_t));
    struct sockaddr_in sockaddr;

    cli->sockid = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(av[1]);
    sockaddr.sin_port = htons(atoi(av[2]));
    if (connect(cli->sockid, (struct sockaddr *)&sockaddr,\
     sizeof(sockaddr)) < 0) {
        perror("Error on connect\n");
        exit(0);
    }
    loop(cli);
    return 0;
}
