/*
** EPITECH PROJECT, 2021
** client
** File description:
** converter
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
    tmp = malloc(sizeof(char) * (size + words + 1));
    tmp[0] = '\0';
    for (int i = start; str[i]; i++) {
        tmp = strcat(tmp, str[i]);
        tmp = strcat(tmp, " ");
    }
    tmp[size + words] = '\0';
    tmp = strdup(tmp);
    return tmp;
}