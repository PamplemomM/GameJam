/*
** EPITECH PROJECT, 2024
** rect_lib.c
** File description:
** The file for the rectangle functions.
*/
#include "../include/header.h"

rect_t **all_rects(void)
{
    static rect_t *rect_list = NULL;

    return &rect_list;
}

static void rect_add(rect_t *rect)
{
    rect_t **rect_list = all_rects();

    rect->next = *rect_list;
    *rect_list = rect;
}

rect_t *find_rect(char *name)
{
    rect_t *all_rect = *all_rects();

    while (all_rect != NULL) {
        if (my_strcmp(name, all_rect->name) == 0) {
            return all_rect;
        }
        all_rect = all_rect->next;
    }
    my_putstr("rect Non Trouvé\n");
    return NULL;
}

rect_t *create_rect(char *name, sfVector2f position, int size)
{
    rect_t *new_rect = malloc(sizeof(rect_t));

    if (new_rect == NULL)
        return NULL;
    new_rect->name = my_strdup(name);
    new_rect->shape = sfRectangleShape_create();
    sfRectangleShape_setSize(new_rect->shape, (sfVector2f){size, size});
    sfRectangleShape_setPosition(new_rect->shape, position);
    new_rect->pos = position;
    sfRectangleShape_setFillColor(new_rect->shape, sfWhite);
    new_rect->color = sfWhite;
    sfRectangleShape_setOutlineColor(new_rect->shape, (sfColor){128, 128, 128, 255});
    sfRectangleShape_setOutlineThickness(new_rect->shape, 1);
    new_rect->height = 0;
    new_rect->distance = 1;
    new_rect->rotation = 0.0;
    new_rect->hide = 1;
    new_rect->other = 0.0;
    new_rect->speed = 1.0;
    rect_add(new_rect);
    return new_rect;
}

static void rect_destroy(rect_t *rect)
{
    sfRectangleShape_destroy(rect->shape);
    free(rect->name);
    free(rect);
}

void reset_all_rects(void)
{
    rect_t *current = *all_rects();
    rect_t *next;

    while (current != NULL) {
        next = current->next;
        rect_destroy(current);
        current = next;
    }
    *all_rects() = NULL;
}

void move_rect(rect_t *rect, float x, float y)
{
    rect->pos.x += x;
    rect->pos.y += y;
    sfRectangleShape_move(rect->shape, (sfVector2f){x, y});
}