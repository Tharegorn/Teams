/*
** EPITECH PROJECT, 2019
** get_next_line.c
** File description:
** getnextline.c
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static char *my_strncpy(char *res, char *str, int counter)
{
    int count = 0;

    while (str[count] != '\0' && count < counter) {
        res[count] = str[count];
        count++;
    }
    if (counter < count)
        res[count] = '\0';
    return (res);
}

static char *add_line(char *l, int count, char *stock, int *n)
{
    char *lengh;
    int oldvalue;

    if (l != 0)
        oldvalue = strlen(l);
    else
        oldvalue = 0;
    lengh = malloc((oldvalue + count + 1) * sizeof(*lengh));
    if (l != 0)
        my_strncpy(lengh, l, oldvalue);
    else
        my_strncpy(lengh, "", oldvalue);
    lengh[oldvalue + count] = 0;
    my_strncpy(lengh + oldvalue, stock + *n, count);
    if (l)
        free(l);
    *n = *n + (count + 1);
    return (lengh);
}

char *make(int fd, int rd)
{
    char stock[rd];
    static int current_arg = 0;
    static int n;
    int count = 0;
    char *l = NULL;

    while (1 == 1) {
        if (current_arg <= n) {
            n = 0;
            if (!(current_arg = read(fd, stock, rd)))
                return (l);
            if (current_arg == -1)
                return (NULL);
            count = 0;
        }
        if (stock[n + count] == '\n')
            return (l = add_line(l, count, stock, &n));
        if (n + count == current_arg - 1)
            l = add_line(l, count + 1, stock, &n);
        count++;
    }
}

char *get_next_line(int fd)
{
    int rd = 200;

    if (rd >= 1000 || rd <= 0)
        return (NULL);
    else
        return (make(fd, rd));
}
