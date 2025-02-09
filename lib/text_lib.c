/*
** EPITECH PROJECT, 2024
** text_lib.c
** File description:
** The file for the text management (create, operate).
*/
#include "../include/header.h"

text_t **all_texts(void)
{
    static text_t *text_list = NULL;

    return &text_list;
}

static void text_add(text_t *text)
{
    text_t **text_list = all_texts();

    text->next = *text_list;
    *text_list = text;
}

text_t *find_text(char *name)
{
    text_t *all_text = *all_texts();

    while (all_text != NULL) {
        if (my_strcmp(name, all_text->name) == 0) {
            return all_text;
        }
        all_text = all_text->next;
    }
    my_putstr("Texte Non Trouvé\n");
    return NULL;
}

void create_text(char *name, sfVector2f position, int size,
    char const *font_path)
{
    text_t *new_text = malloc(sizeof(text_t));

    if (new_text == NULL)
        return;
    new_text->name = my_strdup(name);
    new_text->text = sfText_create();
    if (*all_texts() == NULL)
        new_text->font = sfFont_createFromFile(font_path);
    else
        new_text->font = (*all_texts())->font;
    sfText_setFont(new_text->text, new_text->font);
    sfText_setPosition(new_text->text, position);
    new_text->pos = position;
    new_text->hide = 0;
    new_text->rotation = 0.0;
    sfText_setScale(new_text->text, (sfVector2f){size, size});
    new_text->size = size;
    sfText_setString(new_text->text, name);
    text_add(new_text);
}

static void text_destroy(text_t *text)
{
    sfText_destroy(text->text);
    free(text->name);
    free(text);
}

void reset_all_texts(void)
{
    text_t *current = *all_texts();
    text_t *next;

    while (current != NULL) {
        next = current->next;
        text_destroy(current);
        current = next;
    }
    *all_texts() = NULL;
}
