/*
** EPITECH PROJECT, 2024
** sprite_chained_list.c
** File description:
** The function that manage the sprites within chained lists.
*/
#include "../include/header.h"
#include <stddef.h>

sprite_t **all_sprites(void)
{
    static sprite_t *spritelist = NULL;

    return &spritelist;
}

void sprite_add(sprite_t *new_sprite)
{
    new_sprite->next = *all_sprites();
    *all_sprites() = new_sprite;
}

sprite_t *find_sprite(char *name)
{
    sprite_t *all_sprite = *all_sprites();

    while (all_sprite != NULL) {
        if (my_strcmp(name, all_sprite->name) == 0) {
            return all_sprite;
        }
        all_sprite = all_sprite->next;
    }
    my_putstr("Sprite Non Trouvé\n");
    return NULL;
}

void reset_all_sprites(sprite_t **all_sprite)
{
    sprite_t *current = *all_sprite;
    sprite_t *next;

    while (current != NULL) {
        next = current->next;
        sprite_destroy(current);
        current = next;
    }
    *all_sprite = NULL;
}
