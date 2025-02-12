/*
** EPITECH PROJECT, 2025
** raycast.c
** File description:
** The file for the raytracing.
*/
#include "include/header.h"

int init_raycasters(void)
{
    rect_t *actual;
    char *name;
    char *number;

    for (int i = 0; i < FOV * FOV_PRECISION; i++) {
        number = my_its(i);
        name = my_sec_strcat("cast", number);
        actual = create_rect(name, (sfVector2f){200, 500}, 10);
        if (actual == NULL)
            return ERROR;
        sfRectangleShape_setOrigin(actual->shape, (sfVector2f){5, 5});
        sfRectangleShape_setFillColor(actual->shape, sfRed);
        free(number);
        free(name);
        number = my_its(i);
        name = my_sec_strcat("wall", number);
        actual = create_rect(name, (sfVector2f){STARTX, STARTY}, 10);
        if (actual == NULL)
        return ERROR;
        actual->color = (sfColor){255, 255, 255, 255};
        actual->hide = 1;
        sfRectangleShape_setFillColor(actual->shape, actual->color);
        free(number);
        free(name);
    }
    return SUCESS;
}

void size_casts(rect_t *cast, rect_t *wall, int x, rect_t *player)
{
    cast->distance *= cos((cast->rotation - player->rotation) * PI / 180.0);
    if (cast->distance < BLOCK_SIZE - (BLOCK_SIZE / 2.2))
        cast->distance = 15;
    wall->height = SCREEN_SIZE_Y * 15 / (cast->distance * 1.5);
    wall->pos.x = x;
    wall->pos.y = 400; // (SCREEN_SIZE_Y * BLOCK_SIZE) / 2;
    sfRectangleShape_setPosition(wall->shape, wall->pos);
    sfRectangleShape_setScale(wall->shape, (sfVector2f){2, (int)(SCREEN_SIZE_Y * wall->height)/* % SCREEN_SIZE_Y * BLOCK_SIZE*/});
    sfRectangleShape_setOrigin(wall->shape, (sfVector2f){0, + wall->height / 2});
    if (cast->distance < RENDER_DISTANCE)
        sfRenderWindow_drawRectangleShape(*get_window(), wall->shape, NULL);
    wall->color.r = 255 - (int)((int)(cast->distance) / 3.5) % 255;
    wall->color.g = 255 - (int)((int)(cast->distance) / 3.5) % 255;
    wall->color.b = 255 - (int)((int)(cast->distance) / 3.5) % 255;
    sfRectangleShape_setFillColor(wall->shape, wall->color);
}

static int throw_cast(room_t *room, rect_t *cast)
{
    sfVector2f mv = {0, 0};
    sfVector2f initial_pos = cast->pos;

    while (room->intmap[(int)((cast->pos.y) / BLOCK_SIZE) * room->size.x + (int)((cast->pos.x) / BLOCK_SIZE)] != 1) {
        mv.x = cos(cast->rotation * PI / 180.0) * CAST_SPEED;
        mv.y = sin(cast->rotation * PI / 180.0) * CAST_SPEED;
        cast->pos.x += mv.x;
        cast->pos.y += mv.y;
        sfRectangleShape_move(cast->shape, mv);
    }
    while (room->intmap[(int)((cast->pos.y) / BLOCK_SIZE) * room->size.x + (int)((cast->pos.x) / BLOCK_SIZE)] != 0) {
       mv.x = cos((180 + cast->rotation) * PI / 180.0);
       mv.y = sin((180 + cast->rotation) * PI / 180.0);
       cast->pos.x += mv.x;
       cast->pos.y += mv.y;
       sfRectangleShape_move(cast->shape, mv);
    }
    sfRenderWindow_drawRectangleShape(*get_window(), cast->shape, NULL);
    cast->distance = sqrt(SQ(abs(initial_pos.x - cast->pos.x)) + SQ(abs(initial_pos.y - cast->pos.y)));
    return SUCESS;
}

static int get_all_casts(int x, int cpt, float rotation, rect_t *player)
{
    room_t *room = *get_room();
    char *number = my_its(cpt);
    char *name = my_sec_strcat("cast", number);
    char *wall_name = my_sec_strcat("wall", number);
    rect_t *actual = find_rect(name);
    rect_t *actual_wall;
    
    free(name);
    name = my_sec_strcat("wall", my_its(cpt));
    actual_wall= find_rect(name);
    actual->rotation = rotation;
    sfRectangleShape_setPosition(actual->shape, player->pos);
    actual->pos.x = player->pos.x;
    actual->pos.y = player->pos.y;
    actual->distance = 0;
    throw_cast(room, actual);
    sfRenderWindow_drawRectangleShape(*get_window(), actual->shape, NULL);
    size_casts(actual, actual_wall, x, player);
    free(wall_name);
    free(number);
    free(name);
    return SUCESS;
}


void drawrays(room_t *room, sfEvent event)
{
    rect_t *player = find_rect("player");
    float actual_rotation = 0;
    int cpt = 0;
    int x = STARTX;
    
    actual_rotation = player->rotation - FOV / 2;
    for (int i = 0; actual_rotation <= player->rotation + FOV / 2 && i < FOV * FOV_PRECISION; i++) {
        get_all_casts(x, i, actual_rotation, player);
        actual_rotation += 1/FOV_PRECISION;
        x += 15 * (1 / FOV_PRECISION);
    }
}