/*
** EPITECH PROJECT, 2024
** event_lib.c
** File description:
** The file for the event management lib.
*/
#include "../include/header.h"


float get_actual_time(float multip)
{
    static float current_speed = 1;

    current_speed *= multip;
    return current_speed;
}

void check_cursor_circle(sfCircleShape *c, sfVector2i mPos)
{
    float r = sfCircleShape_getRadius(c);
    sfVector2f pos = (sfVector2f){sfCircleShape_getPosition(c).x + r,
        sfCircleShape_getPosition(c).y + r};
    int powx = (mPos.x - pos.x) * (mPos.x - pos.x);
    int powy = (mPos.y - pos.y) * (mPos.y - pos.y);
    float d = sqrt(powx + powy);

    if (d <= r) {
        sfCircleShape_setFillColor(c, sfRed);
    } else {
        sfCircleShape_setFillColor(c, sfTransparent);
    }
}

void analyse_events(sfEvent event)
{
    while (sfRenderWindow_pollEvent(*get_window(), &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(*get_window());
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyE) {
            my_putstr("Segmentation Fault (core dumped)\n");
            sfRenderWindow_close(*get_window());
        }
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyP)
            find_rect("player")->speed++;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            find_sprite("transition")->type = 0;
    }
}
