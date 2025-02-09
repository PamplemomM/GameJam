/*
** EPITECH PROJECT, 2024
** tools_c_func_mr.c
** File description:
** The file for the tools functions.
*/
#include "../include/header.h"

char *my_sec_strcat(char *dest, char const *src)
{
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    char *res = malloc(sizeof(char) * (len_dest + len_src + 1));

    if (res == NULL)
        return NULL;
    for (int i = 0; i < len_dest; i++) {
        res[i] = dest[i];
    }
    for (int i = 0; i < len_src; i++) {
        res[len_dest + i] = src[i];
    }
    res[len_dest + len_src] = '\0';
    return res;
}

static void my_revstr(char *str)
{
    int i = 0;
    int j = my_strlen(str) - 1;
    char res;

    while (str[i] != '\0' && i < j) {
        res = str[i];
        str[i] = str[j];
        str[j] = res;
        i++;
        j--;
    }
}

char *my_its(int nbr)
{
    int i = 0;
    char *result = malloc(sizeof(char) * (12 + 1));

    if (result == NULL)
        return NULL;
    if (nbr < 10) {
        DO_THEN(DO_THEN(result[0] = '0', result[1] = 48 + nbr), result[2] = '\0');
        return result;
    }
    while (nbr > 0) {
        result[i] = (nbr % 10) + 48;
        nbr = nbr / 10;
        i++;
    }
    result[i] = '\0';
    my_revstr(result);
    return result;
}

int my_getnbr(char *str, int *i)
{
    int res = 0;

    while (str[*i] && (str[*i] < '0' || str[*i] > '9'))
        (*i)++;
    while (str[*i] >= '0' && str[*i] <= '9') {
        res = res * 10 + (str[*i] - '0');
        (*i)++;
    }
    return res;
}

char *my_fts(float nb)
{
    char *result = my_its((int)(nb * 1000));
    int len = my_strlen(result);
    char temp1 = result[len - 1];
    char temp2 = result[len - 2];
    char temp3 = result[len - 3];

    if ((int)(nb * 1000) < 1000) {
        result[0] = '0';
        len++;
    }
    result[len - 3] = '.';
    result[len - 2] = temp3;
    result[len - 1] = '\0';
    if (nb < 0.5) {
        result[len - 1] = temp2;
        result[len] = temp1;
        result[len + 1] = '\0';
    }
    return result;
}
