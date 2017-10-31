#include "wolf3d.h"
#include <math.h>

void	default_wall(int side, t_rchelp *rc, t_wolf3d *all)
{
	int		color;
	int 	i;

	if (side == 1 && rc->ray.dir.y > 0)
		color = 0xFF1493;
	else if (side == 1)
		color = 0x00FF00;
	else if (side == 0 && rc->ray.dir.x > 0)
		color = 0xFFA500;
	else
		color = 0x00ffff;
	i = 0;
	while (i < rc->start_y)
		all->image.pixels[i++ * WIDTH + rc->x] = 0x87cefa;
	while (i < rc->end_y)
		all->image.pixels[i++ * WIDTH + rc->x] = color;
	while (i < HEIGHT)
		all->image.pixels[i++ * WIDTH + rc->x] = 0x8B4513;
}

void	draw_strip(t_rchelp *rc, int side, t_wolf3d *all)
{
	if (side == 0)
	{
		rc->dist = (rc->mapX - rc->ray.origin.x + (1 - rc->stepX) / 2) / rc->ray.dir.x;
		rc->wall_x = rc->ray.origin.y + rc->dist * rc->ray.dir.y;
	}
	else
	{
		rc->dist = (rc->mapY - rc->ray.origin.y + (1 - rc->stepY) / 2) / rc->ray.dir.y;
		rc->wall_x = rc->ray.origin.x + rc->dist * rc->ray.dir.x;
	}
	rc->line_height = (int) (HEIGHT / rc->dist);
	rc->start_y = -rc->line_height / 2 + HEIGHT / 2;
	rc->start_y = rc->start_y < 0 ? 0 : rc->start_y;
	rc->end_y = rc->line_height / 2 + HEIGHT / 2;
	rc->end_y = rc->end_y >= HEIGHT ? HEIGHT - 1 : rc->end_y;
	rc->wall_x -= (int) rc->wall_x;
	if (all->textures_enabled == NO)
		default_wall(side, rc, all);
	else
	{
		skybox(rc, all);
		textured_wall(side, rc, all);
		textured_floor(side, rc, all);
	}
}