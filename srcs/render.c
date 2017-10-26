#include "wolf3d.h"
#include "mlx.h"
#include "ray_casting.h"
#include <stdio.h>
#include "libft.h"
#include <math.h>

void			draw_line_dda(t_line *line, t_wolf3d *all, int color)
{
	int		deltas[2];
	int		steps;
	int		k;
	float	incs[2];
	float	xy[2];

	deltas[0] = ROUND(line->p2.x) - ROUND(line->p1.x);
	deltas[1] = ROUND(line->p2.y) - ROUND(line->p1.y);
	xy[0] = ROUND(line->p1.x);
	xy[1] = ROUND(line->p1.y);
	steps = ABS(deltas[0]) > ABS(deltas[1]) ? ABS(deltas[0]) : ABS(deltas[1]);
	incs[0] = deltas[0] / (float)steps;
	incs[1] = deltas[1] / (float)steps;
	k = -1;
	while (++k < steps)
	{
		if (IN_RANGE(ROUND(xy[1]), 0, HEIGHT - 1) &&
			IN_RANGE(ROUND(xy[0]), 0, WIDTH - 1))
			all->image.pixels[ROUND(xy[1]) * WIDTH + ROUND(xy[0])] = color;
		xy[0] += incs[0];
		xy[1] += incs[1];
	}
}

void	fill_floor_ceil(int	*pixels)
{
	int i;
	int j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixels[i * WIDTH + j] = 0x87CEEB;
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixels[i * WIDTH + j] = 0x556B2F;
			j++;
		}
		i++;
	}
}

void	render(t_wolf3d *all)
{
	int 	x;
	t_ray 	ray;
	int 	mapX;
	int 	mapY;


	fill_floor_ceil(all->image.pixels);
	ray.origin = all->hero.pos;
	x = -1;
	while(++x < WIDTH)
	{
		double planeCoord = 2 * x / (double)WIDTH - 1;
		ray.dir = v2(all->hero.dir.x - 0.66 * all->hero.dir.y * planeCoord ,
					 all->hero.dir.y + 0.66 * all->hero.dir.x * planeCoord );
		mapX = (int)ray.origin.x;
		mapY = (int)ray.origin.y;

		double sideDistX;
		double sideDistY;

		double deltaDistX = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
		double deltaDistY = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (ray.dir.x < 0)
		{
			stepX = -1;
			sideDistX = (ray.origin.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - ray.origin.x) * deltaDistX;
		}
		if (ray.dir.y < 0)
		{
			stepY = -1;
			sideDistY = (ray.origin.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - ray.origin.y) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (all->map.walls[mapX][mapY] > 0) hit = 1;
		}

		if (side == 0) perpWallDist = (mapX - ray.origin.x + (1 - stepX) / 2) / ray.dir.x;
		else           perpWallDist = (mapY - ray.origin.y + (1 - stepY) / 2) / ray.dir.y;

		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

		t_line line = (t_line){v2(x, drawStart), v2(x, drawEnd)};
		int 	color;
		if (side == 1)
			color = 0x0000ff;
		else
			color = 0xff0000;

		draw_line_dda(&line, all, color);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->image.image, 0, 0);
}