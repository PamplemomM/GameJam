/*
** EPITECH PROJECT, 2024
** header.h
** File description:
** Header of the my_radar project.
*/
#ifndef HEADER_H
    #define HEADER_H

    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <time.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <math.h>
    #include <fcntl.h>

    //macros :
    #define SQ(a) (a * a)
    #define PI 3.141592653589793238462
    #define IFDO(condition, action) if ((condition)) {action;}
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define DO_THEN(action1, action2) action1; action2

    //defines :
    #define SUCESS 0
    #define ERROR 84
    #define ROOM_X_SIZE 37
    #define ROOM_Y_SIZE 21
    #define BLOCK_SIZE 50
    #define MAP_OBSTACLES 10
    #define FRUIT_NUMBER 4
    #define CAST_SPEED 10 // speed of the cast projection, the faster it goes, the less precise it is
    #define FOV 120 // Field of view, in angle
    #define FOV_PRECISION 1.5 // ray cast by angle, here, one ray each 2 degree
    #define STARTX 400
    #define STARTY 0
    #define SCREEN_SIZE_X 16
    #define SCREEN_SIZE_Y 16
    #define RENDER_DISTANCE 830

typedef struct room {
    int **map;
    int *intmap;
    sfVector2i size;
    sfVector2i entrance;
    sfVector2i exit;
} room_t;

typedef struct sprite_s {
    char *name;
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f pos;
    sfVector2f dest;
    sfVector2f velocity;
    float speed;
    int delay;
    float rotation;
    int type;
    int hide;
    int other;
    struct sprite_s *next;
} sprite_t;

typedef struct text_s {
    char *name;
    sfFont *font;
    sfText *text;
    sfVector2f pos;
    sfVector2f move;
    sfVector2f velocity;
    float rotation;
    int size;
    int hide;
    float other;
    struct text_s *next;
} text_t;

typedef struct rect_s {
    char *name;
    sfRectangleShape *shape;
    sfSprite *sprite;
    sfVector2f pos;
    sfColor color;
    sfColor outline;
    int thickness;
    float height;
    float distance;
    float rotation;
    int hide;
    float other;
    float speed;
    struct rect_s *next;
} rect_t;

//window_lib.c
sfRenderWindow **get_window(void);
void init_window(char *name, unsigned int width, unsigned int height);
void destroy_window(void);
void end_it_all(int exiting_number);

//sprite_lib.c
void sprite_create(char *name, char const *texture_path, sfVector2f position);
void sprite_destroy(sprite_t *sprite);
void verify_my_sprite(char *str);
void move_sprite(sprite_t *sprite, float x, float y);

//sprite_chained_list_lib.c
sprite_t **all_sprites(void);
void sprite_add(sprite_t *new_sprite);
sprite_t *find_sprite(char *name);
void reset_all_sprites(sprite_t **all_sprite);

//event_lib.c
float get_actual_time(float multip);
void check_cursor_circle(sfCircleShape *c, sfVector2i pos);
void analyse_events(sfEvent event);

//c_functions.c
int my_strlen(char const *str);
char *my_strdup(char const *src);
int my_putstr(char const *str);
int my_strcmp(char const *s1, char const *s2);
int mini_printf(const char *format, ...);

//tools_c_func_mr.c
char *my_sec_strcat(char *dest, char const *src);
char *my_its(int nbr);
int my_getnbr(char *str, int *i);

//my_str_to_word_array.c
char *my_fts(float nb);
char **my_str_to_word_array(char *str, int i, int j, int k);
void free_word_array(char **wa);

//rect_lib.c
rect_t **all_rects(void);
rect_t *find_rect(char *name);
rect_t *create_rect(char *name, sfVector2f position, int size);
void reset_all_rects(void);
void move_rect(rect_t *rect, float x, float y);


//text_lib.c
text_t **all_texts(void);
text_t *find_text(char *name);
void create_text(char *name, sfVector2f position, int size,
    char const *font_path);
void reset_all_texts(void);

//stuffs.c
sfClock **get_clock(void);
float get_time(void);
int get_seconds(void);
int diceroll(int low, int high);

//init_rt.c
sfTexture **get_fruit_texture(void);
void init_sprites(void);

//room_generator.c
room_t **get_room(void);
void free_current_room(void);
void print_map(void);
void make_room(int x, int y);
void replace_char(char *ch, char chifn, char chnew, char chelse);

// raycast.c
int init_raycasters(void);
void drawrays(room_t *room, sfEvent event);

#endif /* HEADER_H */
