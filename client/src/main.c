/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** main
*/

#include "client.h"

char *message_convert(char **str, int start)
{
    char *tmp = NULL;
    int size = 0;
    int words = 0;

    if (str[3] == NULL)
        return str[2];
    for (int i = start; str[i]; i++, words++)
        size += strlen(str[i]);
    tmp = malloc(sizeof (char) * (size + words + 1));
    tmp[0] = '\0';
    for (int i = start; str[i]; i++) {
        tmp = strcat(tmp, str[i]);
        tmp = strcat(tmp, " ");
    }
    tmp[size + words] = '\0';
    tmp = strdup(tmp);
    return tmp;
}

void receive(client_t *cli)
{
    char **arr = NULL;
    char buffer[5024];
    int len = 0;

    if ((len = recv(cli->sockid, buffer, 5024 - 1, 0)) < 0)
        return;
    buffer[len] = 0;
    arr = str_warray(buffer, ' ');
    if (strcmp(arr[0], "LOGIN") == 0) {
        cli->name = strdup(arr[2]);
        cli->user_uuid = strdup(arr[1]);
        cli->log_status = YES;
        client_event_logged_in(cli->user_uuid, cli->name);
    }
    if (strcmp(arr[0], "USER") == 0) {
        if (strcmp(arr[1], "NULL") == 0)
            client_error_unknown_user(arr[2]);
        else
            client_print_user(arr[2], arr[1], atoi(arr[3]));
    }
    if (strcmp(arr[0], "PM") == 0) {
        if (strcmp(arr[1], "NULL") == 0)
            client_error_unknown_user(arr[2]);
        else {
            client_event_private_message_received(arr[1], message_convert(arr, 2));
        }
    }
    if (strcmp(arr[0], "MSG") == 0) {
        if (strcmp(arr[1], "NULL") == 0)
            client_error_unknown_user(arr[2]);
        else if (strcmp(arr[1], "ANY") == 0)
            printf("No pm with this User\n");
        else {
            client_private_message_print_messages(arr[1], (time_t)atoi(arr[2]), message_convert(arr, 3));
        }
    }
    if (strcmp(arr[0], "USERS") == 0)
        client_print_user(arr[2], arr[1], atoi(arr[3]));
    if (strcmp(arr[0], "LOGOUT") == 0) {
        if (cli->log_status == YES)
            client_event_logged_out(cli->user_uuid, cli->name);
        exit(0);
    }
}

void send_to_server(client_t *cli, char *line)
{
    char **arr = str_warray(line, ' ');

    if (arr[0] == NULL)
        return;
    if (strcmp(arr[0], "/logout") == 0) {
        if (cli->log_status == YES)
            client_event_logged_out(cli->user_uuid, cli->name);
        dprintf(cli->sockid, "LOGOUT\n");
        exit(0);
    }
    if (strcmp(arr[0], "/login") == 0) {
        if (cli->log_status == YES)
            client_error_already_exist();
        else {
            if (arr[1] == NULL)
                client_error_unauthorized();
            else
                dprintf(cli->sockid, "LOGIN %s\n", arr[1]);
        }
    }
    if (strcmp(arr[0], "/user") == 0) {
        if (cli->log_status == NO) {
            client_error_unauthorized();
            return;
        }
        if (arr[1] == NULL)
            printf("INVALID UUID\n");
        else
            dprintf(cli->sockid, "USER %s\n", arr[1]);
    }
    if (strcmp(arr[0], "/help") == 0)
        dprintf(cli->sockid, "HELP\n");
    if (strcmp(arr[0], "/send") == 0) {
        if (cli->log_status == NO) {
            client_error_unauthorized();
            return;
        }
        if (arr[1] == NULL || arr[2] == NULL)
            printf("Invalid Command : /send <user_uuid> <message_body>\n");
        else {
            dprintf(cli->sockid, "PM %s ", arr[1]);
            for (int i = 2; arr[i]; i++)
                dprintf(cli->sockid, "%s ", arr[i]);
            dprintf(cli->sockid, "\n");
        }
    }
    if (strcmp(arr[0], "/messages") == 0) {
        if (arr[1] == NULL || cli->log_status == NO)
            client_error_unauthorized();
        else
            dprintf(cli->sockid, "MSG %s\n", arr[1]);
    }
    if (strcmp(arr[0], "/users") == 0) {
        if (cli->log_status == NO)
            client_error_unauthorized();
        else
            dprintf(cli->sockid, "USERS\n");
    }
}

void loop(client_t *cli)
{
    fd_set rfd;
    while (1) {
        FD_ZERO(&rfd);
        FD_SET(STDIN_FILENO, &rfd);
        FD_SET(cli->sockid, &rfd);
        if (select(cli->sockid + 1, &rfd, NULL, NULL, NULL) < 0)
            break;
        if (FD_ISSET(STDIN_FILENO, &rfd)) {
            send_to_server(cli, get_next_line(0));
        } else if (FD_ISSET(cli->sockid, &rfd)) {
            receive(cli);
        }
    }
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
    if (connect(cli->sockid, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
        perror("Error on connect\n");
        exit (0);
    }
    loop(cli);
    // close(cli->sockid);
    return 0;
}
