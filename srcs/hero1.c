#include "hero.h"

int				check_move(double x, double y, int  **walls)
{
	int		mapX;
	int 	mapY;
	double	t[4];// x - mapX, (mapX + 1) - x, y - mapY, (mapY + 1) - y

	mapX = (int)x;
	mapY = (int)y;
	t[0] = x - mapX;
	t[1] = (mapX + 1) - x;
	t[2] = y - mapY;
	t[3] = (mapY + 1) - y;

	if (walls[mapY][mapX] == 0)
	{
		if ((walls[mapY][mapX - 1] && t[0] < 0.1) ||
			(walls[mapY][mapX + 1] && t[1] < 0.1) ||
			(walls[mapY - 1][mapX] && t[2] < 0.1) ||
			(walls[mapY + 1][mapX] && t[3] < 0.1) ||
			(walls[mapY - 1][mapX - 1] && (t[0] < 0.1 && t[2] < 0.1)) ||
			(walls[mapY - 1][mapX + 1] && (t[1] < 0.1 && t[2] < 0.1)) ||
			(walls[mapY + 1][mapX - 1] && (t[0] < 0.1 && t[3] < 0.1)) ||
			(walls[mapY + 1][mapX + 1] && (t[1] < 0.1 && t[3] < 0.1)))
			return (0);
		return (1);
	}
	return (0);
}

void            hero_move_forward(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x + hero->dir.x * 0.1, hero->pos.y, map->walls))
    	hero->pos.x += hero->dir.x * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y + hero->dir.y * 0.1, map->walls))
		hero->pos.y += hero->dir.y * MOVE_SPEED * hero->speed;
}

void            hero_move_backward(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x - hero->dir.x * 0.1, hero->pos.y, map->walls))
		hero->pos.x -= hero->dir.x * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y - hero->dir.y * 0.1, map->walls))
		hero->pos.y -= hero->dir.y * MOVE_SPEED * hero->speed;
}


void            hero_move_left(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x + hero->dir.y * 0.1, hero->pos.y, map->walls))
		hero->pos.x += hero->dir.y * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y - hero->dir.x * 0.1, map->walls))
		hero->pos.y -= hero->dir.x * MOVE_SPEED * hero->speed;
}

void            hero_move_right(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x - hero->dir.y * 0.1, hero->pos.y, map->walls))
		hero->pos.x -= hero->dir.y * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y + hero->dir.x * 0.1, map->walls))
		hero->pos.y += hero->dir.x * MOVE_SPEED * hero->speed;
}