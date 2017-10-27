#include "wolf3d.h"
#include <math.h>

void	assign_step_and_sideDist(t_rchelp *rc)
{
	if (rc->ray.dir.x < 0)
	{
		rc->stepX = -1;
		rc->sideDist.x = (rc->ray.origin.x - rc->mapX) * rc->deltaDist.x;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDist.x = (rc->mapX + 1.0 - rc->ray.origin.x) * rc->deltaDist.x;
	}
	if (rc->ray.dir.y < 0)
	{
		rc->stepY = -1;
		rc->sideDist.y = (rc->ray.origin.y - rc->mapY) * rc->deltaDist.y;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDist.y = (rc->mapY + 1.0 - rc->ray.origin.y) * rc->deltaDist.y;
	}
}

void	prepare_ray_casting(t_rchelp *rc, t_hero *hero)
{
	double planeCoord;

	planeCoord = 2 * rc->x / (double)WIDTH - 1;
	rc->ray.origin = hero->pos;
	rc->ray.dir = v2(hero->dir.x - 0.66 * hero->dir.y * planeCoord ,
					 hero->dir.y + 0.66 * hero->dir.x * planeCoord );
	rc->mapX = (int)rc->ray.origin.x;
	rc->mapY = (int)rc->ray.origin.y;
	rc->deltaDist.x = sqrt(1 + (rc->ray.dir.y * rc->ray.dir.y) /
							   (rc->ray.dir.x * rc->ray.dir.x));
	rc->deltaDist.y = sqrt(1 + (rc->ray.dir.x * rc->ray.dir.x) /
							   (rc->ray.dir.y * rc->ray.dir.y));
	assign_step_and_sideDist(rc);
}

int	ray_casting(t_rchelp *rc, t_map *map)
{
	int	side;

	while (1)
	{
		if (rc->sideDist.x < rc->sideDist.y)
		{
			rc->sideDist.x += rc->deltaDist.x;
			rc->mapX += rc->stepX;
			side = 0;
		}
		else
		{
			rc->sideDist.y += rc->deltaDist.y;
			rc->mapY += rc->stepY;
			side = 1;
		}
		if (map->walls[rc->mapX][rc->mapY] > 0)
		{
			rc->tex_num = map->walls[rc->mapX][rc->mapY] - 1;
			break;
		}
	}
	return (side);
}