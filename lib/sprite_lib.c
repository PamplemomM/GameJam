/*
** EPITECH PROJECT, 2024
** graphical_lib.c
** File description:
** Function to simplificate the SFML projects.
*/
#include "../include/header.h"

void sprite_create(char *name, char const *texture_path, sfVector2f position)
{
    sprite_t *new_sprite = malloc(sizeof(sprite_t));

    if (new_sprite == NULL)
        return;
    new_sprite->name = my_strdup(name);
    new_sprite->texture = sfTexture_createFromFile(texture_path, NULL);
    new_sprite->sprite = sfSprite_create();
    sfSprite_setTexture(new_sprite->sprite, new_sprite->texture, sfTrue);
    new_sprite->pos = position;
    sfSprite_setPosition(new_sprite->sprite,
        (sfVector2f){position.x, position.y});
    new_sprite->velocity = (sfVector2f){0};
    new_sprite->dest = (sfVector2f){0};
    new_sprite->speed = 0;
    new_sprite->delay = 0;
    new_sprite->rotation = 0;
    new_sprite->hide = 0.0;
    new_sprite->other = 0;
    sprite_add(new_sprite);
}

void sprite_destroy(sprite_t *sprite)
{
    sfTexture_destroy(sprite->texture);
    sfSprite_destroy(sprite->sprite);
    free(sprite->name);
    free(sprite);
}

void verify_my_sprite(char *str)
{
    sprite_t *sprite = find_sprite(str);

    if (sprite != NULL) {
        mini_printf("Le sprite '%s' a été trouvé.\n", str);
    } else {
        mini_printf("Le sprite '%s' n'a pas été trouvé.\n", str);
    }
}

void move_sprite(sprite_t *sprite, float x, float y)
{
    sprite->pos.x += x;
    sprite->pos.y += y;
    sfSprite_move(sprite->sprite, (sfVector2f){x, y});
}
