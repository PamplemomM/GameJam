/*
** EPITECH PROJECT, 2024
** window_lib.c
** File description:
** The function for the SFML lib.
*/
#include "../include/header.h"

sfRenderWindow **get_window(void)
{
    static sfRenderWindow *window = NULL;

    return &window;
}

void init_window(char *name, unsigned int width, unsigned int height)
{
    sfVideoMode video_mode = {width, height, 32};
    sfRenderWindow **window_ptr = get_window();

    *window_ptr = sfRenderWindow_create(video_mode, name,
        sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(*window_ptr, 60);
}

void destroy_window(void)
{
    sfRenderWindow **window = get_window();

    if (*window != NULL) {
        sfRenderWindow_destroy(*window);
        *window = NULL;
    }
}

void end_it_all(int exiting_number)
{
    destroy_window();
    reset_all_sprites(all_sprites());
    reset_all_texts();
    reset_all_rects();
    sfClock_destroy(*get_clock());
    mini_printf("Come Back Later !\n");
    exit(exiting_number);
}
