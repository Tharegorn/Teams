/*
** EPITECH PROJECT, 2021
** NTP
** File description:
** wordarray
*/

#include <stdio.h>
#include <stdlib.h>

int clean_str(char c, char f)
{
    if (c >= f + 1)
        return 1;
    else
        return 0;
}

int nb_word(char const *str, char f)
{
    int i = 0;
    int words = 0;

    while (str[i] != '\0') {
        if (clean_str(str[i], f) == 1)
            words++;
        for (; clean_str(str[i], f) == 1 && str[i] != '\0'; i++);
        if (str[i] != '\0')
            i++;
    }
    return words;
}

int len_word(char const *str, int j, char f)
{
    int len = 0;

    for (; clean_str(str[j], f) == 1; j++, len++);
    return len;
}

char **str_warray(char const *str, char f)
{
    char **array = malloc(sizeof(char *) * (nb_word(str, f) + 1));
    int i = 0;
    int j = 0;
    int k = 0;

    for (; i != nb_word(str, f); i++) {
        k = 0;
        for (; clean_str(str[j], f) == 0; j++);
        array[i] = malloc(sizeof(char) * (len_word(str, j, f) + 1));
        for (; clean_str(str[j], f) == 1; k++, j++)
            array[i][k] = str[j];
        array[i][k] = '\0';
    }
    array[i] = NULL;
    return array;
}