/*
** EPITECH PROJECT, 2024
** stuffs.c
** File description:
** The file for the stuffs.
*/
#include "../include/header.h"

sfClock **get_clock(void)
{
    static sfClock *clock;

    return (&clock);
}

float get_time(void)
{
    return (sfClock_getElapsedTime(*get_clock()).microseconds / 1000000.0);
}

int get_seconds(void)
{
    static float seconds = 0;
}

int *get_hitbox(void)
{
    static int hitbox = 1;

    return &hitbox;
}

int diceroll(int low, int high)
{
    if (high < low)
        return high;
    return low + rand() % (high - low);
}