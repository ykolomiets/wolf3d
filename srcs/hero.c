#include "hero.h"
#include <stdio.h>


void            hero_rotate_left(t_hero *hero)
{
    static t_matrix2    rotation_matrix = {
            0.999657324975557,
            -0.026176948307873,
            0.026176948307873,
            0.999657324975557
    };
    static t_matrix2    rotation_matrix_2x = {
            0.998629534754574,
            -0.052335956242944,
            0.052335956242944,
            0.998629534754574
    };

    if (hero->speed == BOOST)
        hero->dir = m2_mult_v2(rotation_matrix_2x, hero->dir);
    else
        hero->dir = m2_mult_v2(rotation_matrix, hero->dir);
}

void            hero_rotate_right(t_hero *hero)
{
    static t_matrix2    rotation_matrix = {
            0.999657324975557,
            0.026176948307873,
            -0.026176948307873,
            0.999657324975557
    };
    static t_matrix2    rotation_matrix_2x = {
            0.998629534754574,
            0.052335956242944,
            -0.052335956242944,
            0.998629534754574
    };

    if (hero->speed == BOOST)
        hero->dir = m2_mult_v2(rotation_matrix_2x, hero->dir);
    else
        hero->dir = m2_mult_v2(rotation_matrix, hero->dir);
}

void            hero_move_forward(t_hero *hero, t_map *map)
{
	if (map->walls
		[(int)(hero->pos.x + hero->dir.x * MOVE_SPEED * hero->speed)]
		[(int)(hero->pos.y)] == 0)
    	hero->pos.x += hero->dir.x * MOVE_SPEED * hero->speed;
	if (map->walls
		[(int)(hero->pos.x)]
		[(int)(hero->pos.y + hero->dir.y * MOVE_SPEED * hero->speed)] == 0)
		hero->pos.y += hero->dir.y * MOVE_SPEED * hero->speed;
}

void            hero_move_backward(t_hero *hero, t_map *map)
{
	if (map->walls
		[(int)(hero->pos.x - hero->dir.x * MOVE_SPEED * hero->speed)]
		[(int)(hero->pos.y)] == 0)
		hero->pos.x -= hero->dir.x * MOVE_SPEED * hero->speed;
	if (map->walls
		[(int)(hero->pos.x)]
		[(int)(hero->pos.y - hero->dir.y * MOVE_SPEED * hero->speed)] == 0)
		hero->pos.y -= hero->dir.y * MOVE_SPEED * hero->speed;
}

void            hero_move_left(t_hero *hero, t_map *map)
{
	if (map->walls
		[(int)(hero->pos.x + hero->dir.y * MOVE_SPEED * hero->speed)]
		[(int)(hero->pos.y)] == 0)
		hero->pos.x += hero->dir.y * MOVE_SPEED * hero->speed;
	if (map->walls
		[(int)(hero->pos.x)]
		[(int)(hero->pos.y - hero->dir.x * MOVE_SPEED * hero->speed)] == 0)
		hero->pos.y -= hero->dir.x * MOVE_SPEED * hero->speed;
}

void            hero_move_right(t_hero *hero, t_map *map)
{
	if (map->walls
		[(int)(hero->pos.x - hero->dir.y * MOVE_SPEED * hero->speed)]
		[(int)(hero->pos.y)] == 0)
		hero->pos.x -= hero->dir.y * MOVE_SPEED * hero->speed;
	if (map->walls
		[(int)(hero->pos.x)]
		[(int)(hero->pos.y + hero->dir.x * MOVE_SPEED * hero->speed)] == 0)
		hero->pos.y += hero->dir.x * MOVE_SPEED * hero->speed;
}

void            hero_zoom_in(t_hero *hero)
{
    hero->zoom += 0.1;
    if (hero->zoom > 2)
        hero->zoom = 2;
}

void            hero_zoom_out(t_hero *hero)
{
    hero->zoom -= 0.1;
    if (hero->zoom < 1)
        hero->zoom = 1;
}