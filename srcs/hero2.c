#include "hero.h"

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