/*
** EPITECH PROJECT, 2025
** init_rt.c
** File description:
** The file for the initialisation of the rt.
*/
#include "include/header.h"

sfTexture **get_fruit_texture(void)
{
    static sfTexture *texture = NULL;

    return &texture;
}

static void init_env(rect_t *player)
{
    room_t *room = (*get_room());

    player->other = room->intmap[(int)(player->pos.y / BLOCK_SIZE) * room->size.x + (int)(player->pos.x / BLOCK_SIZE)];
}

void init_sprites(void)
{
    *get_fruit_texture() = sfTexture_createFromFile("images/apple.png", NULL);
    sprite_create("transition", "images/pinwheel/01.png", (sfVector2f){0, -420});
    sprite_create("blur", "images/blur/01.png", (sfVector2f){0, 0});
    find_sprite("blur")->hide = 1;
    sfSprite_setTextureRect(find_sprite("transition")->sprite, (sfIntRect){0, 0, 1920, 1080});
    sprite_create("enter", "images/enter.png", (sfVector2f){680, 500});
    sfSprite_setScale(find_sprite("enter")->sprite, (sfVector2f){0.7, 0.7});
    sfSprite_setColor(find_sprite("enter")->sprite, (sfColor){255, 255, 255, 150});
    DO_THEN(find_sprite("transition")->hide = 1, find_sprite("transition")->speed = 1);
    create_rect("wall", (sfVector2f){0}, 50);
    sprite_create("gg", "images/pinwheel/08.png", (sfVector2f){0, -420});
    create_rect("player", (sfVector2f){200, 500}, 10);
    sfRectangleShape_setOrigin(find_rect("player")->shape, (sfVector2f){5, 5});
    create_rect("playerline", (sfVector2f){200, 500}, 25);
    sfRectangleShape_setSize(find_rect("playerline")->shape, (sfVector2f){45, 1});
    init_env(find_rect("player"));
    create_text("Timer", (sfVector2f){50, 200}, 2, "polices/Bebas.ttf");
    sfText_setString(find_text("Timer")->text, "Time remaining : 00");
    find_text("Timer")->other = 11;
    sfText_setOutlineThickness(find_text("Timer")->text, 3);
    create_text("score", (sfVector2f){50, 50}, 2, "polices/Bebas.ttf");
    sfText_setString(find_text("score")->text, "");
    find_text("score")->other = 0;
    sfText_setOutlineThickness(find_text("score")->text, 3);
    sprite_create("timer", "images/timer.png", (sfVector2f){1750, 50});
    sfSprite_setTextureRect(find_sprite("timer")->sprite, (sfIntRect){0, 0, 62, 120});
    find_sprite("timer")->other = 1;
}
