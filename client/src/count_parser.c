/*
** EPITECH PROJECT, 2021
** my_teams
** File description:
** count_parser
*/

#include "client.h"

int count_parser(char *str)
{
    int nb = 0;

    if (str == NULL)
        return 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == 34)
            nb++;
    return nb;
}