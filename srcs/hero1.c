#include "hero.h"
#include <stdio.h>

void			draw_map(t_map *map, int heroX, int heroY)
{
	printf("MAP: \n");
	for (int i = 0; i < map->rows; i++)
	{
		for (int j = 0; j < map->cols; j++)
		{
			if (i == heroY && j == heroX)
				printf("X ");
			else
				printf("%d ", map->walls[i][j]);
		}
		printf("\n");
	}
}

int				check_move(double x, double y, t_map *map)
{
	int		mapX;
	int 	mapY;

	mapX = (int)x;
	mapY = (int)y;
	draw_map(map, mapX, mapY);
	if (map->walls[mapY][mapX] == 0)
	{
		if ((map->walls[mapY][mapX - 1] && x - (mapX - 1) < 0.2) ||
			(map->walls[mapY][mapX + 1] && (mapX + 1) - x < 0.2) ||
			(map->walls[mapY - 1][mapX] && y - (mapY - 1) < 0.2) ||
			(map->walls[mapY + 1][mapX] && (mapY + 1) - y < 0.2))
			return (0);
		return (1);
	}
	else
		return (0);
}

void            hero_move_forward(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x + hero->dir.x * 0.1, hero->pos.y, map))
    	hero->pos.x += hero->dir.x * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y + hero->dir.y * 0.1, map))
		hero->pos.y += hero->dir.y * MOVE_SPEED * hero->speed;
}

void            hero_move_backward(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x - hero->dir.x * 0.1, hero->pos.y, map))
		hero->pos.x -= hero->dir.x * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y - hero->dir.y * 0.1, map))
		hero->pos.y -= hero->dir.y * MOVE_SPEED * hero->speed;
}


void            hero_move_left(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x + hero->dir.y * 0.1, hero->pos.y, map))
		hero->pos.x += hero->dir.y * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y - hero->dir.x * 0.1, map))
		hero->pos.y -= hero->dir.x * MOVE_SPEED * hero->speed;
}

void            hero_move_right(t_hero *hero, t_map *map)
{
	if (check_move(hero->pos.x - hero->dir.y * 0.1, hero->pos.y, map))
		hero->pos.x -= hero->dir.y * MOVE_SPEED * hero->speed;
	if (check_move(hero->pos.x, hero->pos.y + hero->dir.x * 0.1, map))
		hero->pos.y += hero->dir.x * MOVE_SPEED * hero->speed;
}