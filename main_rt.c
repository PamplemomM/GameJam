/*
** EPITECH PROJECT, 2025
** main_rt.c
** File description:
** The file for the raytracing.
*/
#include "include/header.h"

static int draw_all_sprites(void)
{
    sprite_t *current = *all_sprites();
    sfRectangleShape *shape = find_rect("playerline")->shape;
    rect_t *player = find_rect("player");
    text_t *timer = find_text("Timer");
    text_t *score = find_text("score");

    timer->other -= 0.016666 * get_actual_time(1);
    sfText_setString(timer->text, my_sec_strcat("Time remaining : ", my_its((int)timer->other)));
    if (find_sprite("timer")->other == 1)
        sfRenderWindow_drawText(*get_window(), timer->text, NULL);
    sfText_setString(score->text, my_sec_strcat(my_sec_strcat(my_sec_strcat("Score : ", (my_its((int)score->other))), "\nSpeed : "), my_its((int)player->speed)));
    sfRenderWindow_drawText(*get_window(), score->text, NULL);
    IFDO(score->other > score->size, score->size = score->other);
    while (current != NULL) {
        if (current->hide = 0)
            sfRenderWindow_drawSprite(*get_window(), current->sprite, NULL);
        current = current->next;
    }
    sfRectangleShape_setPosition(shape, (sfVector2f){player->pos.x, player->pos.y});
    sfRectangleShape_setRotation(shape, player->rotation);
    sfRenderWindow_drawRectangleShape(*get_window(), player->shape, NULL);
    sfRenderWindow_drawRectangleShape(*get_window(), shape, NULL);
    return SUCESS;
}

int draw_map2dcondition(room_t *room, rect_t *wall, int x, int y)
{
    int bloc_position = room->intmap[y * room->size.x + x];

    switch (bloc_position) {
    case 1:
        sfRectangleShape_setFillColor(wall->shape, sfWhite);
        break;
    case 2:
        sfRectangleShape_setFillColor(wall->shape, sfRed);
        break;
    case 3:
        sfRectangleShape_setFillColor(wall->shape, sfBlack);
        break;
    case 4:
        sfRectangleShape_setFillColor(wall->shape, sfWhite);
        break;
    case 5:
        sfRectangleShape_setFillColor(wall->shape, sfRed);
        break;
    default:
        sfRectangleShape_setFillColor(wall->shape, sfBlack);
        break;
    }
    return SUCESS;
}

void draw_map2d(room_t *room)
{
    rect_t *wall = find_rect("wall");

    int x, y, xo, yo;
    for (y = 0; y < room->size.y; y++) {
        for (x = 0; x < room->size.x; x++) {
            draw_map2dcondition(room, wall, x, y);
            sfRectangleShape_setPosition(wall->shape, (sfVector2f){x * BLOCK_SIZE, y * BLOCK_SIZE});
            wall->pos = (sfVector2f){x * BLOCK_SIZE, y * BLOCK_SIZE};
            sfRenderWindow_drawRectangleShape(*get_window(), wall->shape, NULL);
	    }
	}
}

static int detect_fruit(rect_t *player, room_t *room, int value)
{
    int dx[] = {-1, 1, -ROOM_X_SIZE, ROOM_X_SIZE};
    int dy[] = {0, 0, -1, 1};
    int skyzophrenic = 0;
    static float time = 0.0;

    if (get_time() - time > 1.0) {
        skyzophrenic = diceroll(1, 4);
        time = get_time();
    }
    for (int i = 0; i < 4; i++) {
        if (room->intmap[value + dx[i]] == 2 && skyzophrenic == 3)
            room->intmap[value + dx[i]] = room->intmap[value + dx[i] - 2];
        IFDO(room->intmap[value] == 5, room->intmap[value] = room->intmap[value - 1]);
        if (room->intmap[value] == 2) {
            find_sprite("transition")->other = 1;
            room->intmap[value] = 1;
            find_text("score")->other++;
        }
    }
    return SUCESS;
}

static int check_position(rect_t *player, room_t *room)
{
    int change = 0;
    int value = 0;

    if (player->pos.x <= 0 || player->pos.x >= 1847 || player->pos.y <= 0 || player->pos.y >= 998) {
        make_room(ROOM_X_SIZE, ROOM_Y_SIZE);
        room = *get_room();
        player->speed += 0.5;
        change = 1;
    }
    IFDO((player->pos.x <= 0), move_rect(player, 1847, 0));
    IFDO((player->pos.x >= 1847), move_rect(player, -1847, 0));
    IFDO((player->pos.y <= 0), move_rect(player, 0, 997 - abs(player->pos.y)));
    IFDO((player->pos.y >= 998), move_rect(player, 0, -player->pos.y));
    value = (int)(player->pos.y / BLOCK_SIZE) * room->size.x + (int)(player->pos.x / BLOCK_SIZE);
    if (change == 1) {
        player->other = room->intmap[value];
        IFDO(player->other == 3 || player->other == 5, player->other = 1);
        IFDO(player->other == 4, player->other = 2);
    }
    if (room->intmap[value] == 3 || room->intmap[value] == 4 || room->intmap[value] == 2 || room->intmap[value] == 5)
        detect_fruit(player, room, value);
    return SUCESS;
}

static int move_player(sfEvent event, room_t *room)
{
    rect_t *player = find_rect("player");
    sfVector2f move = {0, 0};
    int value = 0;

    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        move.x += cos(player->rotation * PI / 180.0) * player->speed;
        move.y += sin(player->rotation * PI / 180.0) * player->speed;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        move.x -= cos(player->rotation * PI / 180.0) * player->speed;
        move.y -= sin(player->rotation * PI / 180.0) * player->speed;
    }
    IFDO(sfKeyboard_isKeyPressed(sfKeyA), player->rotation -= 5.0);
    IFDO(sfKeyboard_isKeyPressed(sfKeyD), player->rotation += 5.0;);
    value = room->intmap[(int)((player->pos.y + move.y) / BLOCK_SIZE) * room->size.x + (int)((player->pos.x + move.x) / BLOCK_SIZE)];
    if (value == (int)player->other || value == 2 || value == 3 || value == 4) {
        player->pos.x += move.x;
        player->pos.y += move.y;
        sfRectangleShape_move(player->shape, move);
    }
    check_position(player, room);
    return SUCESS;
}
//if needed, take a char * in parametter and change the animation ("images/pinwheel" or "images/circle") and an int for the number of images
static int transition(rect_t *player, room_t *room)
{
    sprite_t *transition = find_sprite("transition");
    static int cpt = 1;
    static int done = 1;

    IFDO(transition->other != 1, return 0);
    IFDO(done == 1, cpt += 2);
    IFDO(done == -1, cpt -= 2);
    if (cpt <= 0) {
        DO_THEN(make_room(ROOM_X_SIZE, ROOM_Y_SIZE), room = *get_room());
        player->other = room->intmap[(int)(player->pos.y / BLOCK_SIZE) * room->size.x + (int)(player->pos.x / BLOCK_SIZE)];
        DO_THEN(DO_THEN(transition->other = 0, done = 1), cpt = 1);
        find_text("Timer")->other = 21;
        return 0;
    }
    IFDO(cpt >= 17, done = -1);
    transition->texture = sfTexture_createFromFile(my_sec_strcat(my_sec_strcat("images/pinwheel/", my_its(cpt)), ".png"), NULL);
    sfSprite_setTexture(transition->sprite, transition->texture, sfTrue);
    sfRenderWindow_drawSprite((*get_window()), transition->sprite, NULL);
    return 1;
}
//find_sprite("transition")->type = Type de menu (menu : 0, game : 1)
//find_text("timer")->other = game timer
//find_text("score")->other = actual score
//(int)find_text("score")->size = best score
int game_launch()
{
    sfEvent event;

    DO_THEN(make_room(ROOM_X_SIZE, ROOM_Y_SIZE), find_text("Timer")->other = 21);
    find_rect("player")->other = (*get_room())->intmap[(int)(find_rect("player")->pos.y / BLOCK_SIZE) * (*get_room())->size.x + (int)(find_rect("player")->pos.x / BLOCK_SIZE)];
    find_sprite("transition")->type = 1;
    DO_THEN(find_text("score")->other = 0, find_rect("player")->speed = 1);
    while (sfRenderWindow_isOpen(*get_window())) {
        sfRenderWindow_clear(*get_window(), sfBlack);
        draw_map2d((*get_room()));
        move_player(event, (*get_room()));
        draw_all_sprites();
        drawrays(*get_room(), event);
        analyse_events(event);
        transition(find_rect("player"), *get_room());
        sfRenderWindow_display(*get_window());
        if (find_sprite("transition")->type == 0 || find_text("Timer")->other <= 0)
            break;
    }
    return SUCESS;
}

static int changemap(void)
{
    sprite_t *blur = find_sprite("blur");
    sfTexture *texture;
    text_t *score = find_text("score");
    static int cpt = 1;
    static float time = 0.0;
    
    sfRenderWindow_drawSprite((*get_window()), find_sprite("blur")->sprite, NULL);
    sfRenderWindow_drawSprite((*get_window()), find_sprite("enter")->sprite, NULL);
    sfRenderWindow_drawSprite((*get_window()), find_sprite("timer")->sprite, NULL);
    sfText_setString(score->text, my_sec_strcat("Best Score : ", (my_its((int)score->size))));
    sfRenderWindow_drawText(*get_window(), score->text, NULL);
    if (get_time() - time < 1.0)
        return 1;
    time = get_time();
    cpt++;
    IFDO(cpt > 8, cpt = 1);
    texture = sfTexture_createFromFile(my_sec_strcat(my_sec_strcat("images/blur/", my_its(cpt)), ".png"), NULL);
    sfSprite_setTexture(blur->sprite, texture, sfTrue);
    return 1;
}

static int check_button(sfEvent event, sprite_t *button)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(button->sprite);
    sfFloatRect bounds_timer = sfSprite_getGlobalBounds(find_sprite("timer")->sprite);


    while (sfRenderWindow_pollEvent(*get_window(), &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(*get_window());
        if (event.type == sfEvtMouseButtonPressed) {
            if (sfFloatRect_contains(&bounds, event.mouseButton.x, event.mouseButton.y))
                game_launch();
            if (sfFloatRect_contains(&bounds_timer, event.mouseButton.x, event.mouseButton.y)) {
                if (find_sprite("timer")->velocity.x == 0) {
                    sfSprite_setTextureRect(find_sprite("timer")->sprite, (sfIntRect){63, 0, 62, 120});
                    find_sprite("timer")->velocity.x = 63;
                    find_sprite("timer")->other = 0;
                } else {
                    sfSprite_setTextureRect(find_sprite("timer")->sprite, (sfIntRect){0, 0, 62, 120});
                    find_sprite("timer")->velocity.x = 0;
                    find_sprite("timer")->other = 1;
                }
            }
        }
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEnter)
            game_launch();
        if (event.type == sfEvtMouseMoved && sfFloatRect_contains(&bounds, event.mouseMove.x, event.mouseMove.y))
            sfSprite_setColor(find_sprite("enter")->sprite, (sfColor){255, 255, 255, 255});
        else
            sfSprite_setColor(find_sprite("enter")->sprite, (sfColor){255, 255, 255, 150});
    }
    return 0;
}


int main(void)
{
    sfEvent event;
    
    *get_clock() = sfClock_create();
    DO_THEN(srand(time(NULL)), init_window("GameJam", 1900, 1080));
    make_room(ROOM_X_SIZE, ROOM_Y_SIZE);
    init_sprites();
    while (sfRenderWindow_isOpen(*get_window())) {
        sfRenderWindow_clear(*get_window(), sfBlack);
        changemap();
        check_button(event, find_sprite("enter"));
        analyse_events(event);
        sfRenderWindow_display(*get_window());
    }
    DO_THEN(free_current_room(), end_it_all(SUCESS));
    return SUCESS;
}