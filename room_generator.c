/*
** EPITECH PROJECT, 2025
** room_generator.c
** File description:
** The file for generating the room.
*/
#include "include/header.h"

room_t **get_room(void)
{
    static room_t *room = NULL;

    return &room;
}

int *map_to_int(int **matrix, int rows, int cols) {
    int *final = malloc(sizeof(int) * rows * cols);

    if (final == NULL)
        return NULL;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            final[i * cols + j] = matrix[i][j];
        }
    }
    return final;
}

void free_current_room(void)
{
    room_t *room = *get_room();

    if (room == NULL)
        return;
    for (int i = 0; room->map[i] != NULL; i++) {
        free(room->map[i]);
    }
    free(room->map);
    free(room->intmap);
    free(room);
}

static void make_floor(int **map, int x, int y)
{
    for (int i = 0; i < x; i++) {
        map[i] = malloc(sizeof(int) * (y + 1));
        if (map[i] == NULL)
            return exit(ERROR);
        for (int j = 0; j < y; j++)
            map[i][j] = 0;
        map[i][y] = -1;
    }
    map[x] = NULL;
}

void replace_char(char *ch, char chifn, char chnew, char chelse)
{
    if (*ch != chifn)
        *ch = chnew;
    else
        *ch = chelse;
}

static void add_obstacle(int **map, int x, int y)
{
    int x1 = diceroll(0, x - 2);
    int y1 = diceroll(0, y - 2);
    int x2 = diceroll(x1 - 1, x - 1);
    int y2 = diceroll(y1 - 1, y - 1);

    for (int i = x1; i < x && i < x2; i++) {
        for (int j = y1; j < y && j < y2; j++)
            map[i][j] = 1;
    }
}

static void add_boundaries(int **map, int x, int y)
{
    for (int i = 0; i < x; i++) {
        map[i][0] = 1;
        map[i][y - 1] = 1;
    }
    for (int j = 1; j < y - 1; j++) {
        map[0][j] = 1;
        map[x - 1][j] = 1;
    }  
}

static void add_doors(int **map, int x, int y, room_t *room)
{
    //int entrance_wall = diceroll(0,3);
    //int exit_wall = diceroll(0,3);

    //map[room->entrance.x][room->entrance.y] = 2;
    //map[room->exit.x][room->exit.y] = 3;
}

static int **make_map(room_t *room, int x, int y)
{
    int **map = malloc(sizeof(int *) * (x + 1));

    if (map == NULL)
        exit(ERROR);
    make_floor(map, x, y);
    for (int i = 0; i < MAP_OBSTACLES; i++)
        add_obstacle(map, x, y);
    //add_boundaries(map, x, y);
    //add_doors(map, x, y, room);
    return map;
}

static sfVector2i valid_proportions(int x, int y)
{
    int xi = x;
    int yi = y;

    if (x >= 3 && y >= 3)
        return (sfVector2i){x, y};
    if (x < 3)
        x = diceroll(3, 30);
    if (y < 3)
        y = diceroll(3, 25);
        while (x + y < 16) {
            if (xi < 3)
            x = diceroll(3, 30);
            if (yi < 3)
            y = diceroll(3, 25);
        }
        return (sfVector2i){x, y};
}

static void add_fruit(int **map, int x, int y, int nb)
{
    int bloc_color = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    int nx = 0;
    int ny = 0;
    int posx = 0;
    int posy = 0;

    for (int i = 0; i < nb; i++) {
        DO_THEN(posx = diceroll(1, x - 2), posy = diceroll(1, y - 2));  
        if (map[posx][posy] == 0 || map[posx][posy] == 1) {
            DO_THEN(bloc_color = map[posx][posy], map[posx][posy] = 2);
            IFDO(diceroll(0, 3) == 1, map[posx][posy] = 5);
            for (int j = 0; j < 4; j++) {
                DO_THEN(nx = posx + dx[j], ny = posy + dy[j]);
                if (nx >= 0 && nx < x && ny >= 0 && ny < y && map[nx][ny] == bloc_color) {
                    IFDO(bloc_color == 0, map[nx][ny] = 3);
                    IFDO(bloc_color == 1, map[nx][ny] = 4);
                }
            }
        }
    }
}



void make_room(int x, int y)
{
    room_t *room = malloc(sizeof(room_t));

    free_current_room();
    if (room == NULL)
        exit(ERROR);
    room->size = valid_proportions(x, y);
    room->map = make_map(room, room->size.y, room->size.x);
    add_fruit(room->map, room->size.y, room->size.x, FRUIT_NUMBER);
    room->intmap = map_to_int(room->map, room->size.y, room->size.x);
    *get_room() = room;
    return;
}



void print_map(void)
{
    room_t *room = *get_room();
    int **map = room->map;
    
    mini_printf("Map d'origine :\n");
    for (int i = 0; map[i] != NULL; i++) {
        for (int j = 0; map[i][j] != -1; j++)
            mini_printf("%d ", map[i][j]);
        mini_printf("\n");
    }
}
