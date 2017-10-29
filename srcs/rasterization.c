#include "wolf3d.h"
#include <stdio.h>

void			draw_line_dda(t_line *line, int *pixels, int color)
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
			pixels[ROUND(xy[1]) * WIDTH + ROUND(xy[0])] = color;
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
			pixels[i * WIDTH + j] = 0x87CEFA;
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pixels[i * WIDTH + j] = 0x8B4513;
			j++;
		}
		i++;
	}
}

void	default_wall(int side, t_rchelp *rc, t_wolf3d *all)
{
	t_line	line;
	int		color;

	line.p1 = v2(rc->x, rc->start_y);
	line.p2 = v2(rc->x, rc->end_y);
	if (side == 1 && rc->ray.dir.y > 0)
		color = 0xFF1493;
	else if (side == 1)
		color = 0x00FF00;
	else if (side == 0 && rc->ray.dir.x > 0)
		color = 0xFFA500;
	else
		color = 0x00ffff;
	draw_line_dda(&line, all->image.pixels, color);
}

void	textured_wall(int side, t_rchelp *rc, t_wolf3d *all)
{
	t_texture	*texture;
	int			tex_x;
	int 		tex_y;
	int 		d;
	int			color;

	texture = &all->textures[rc->tex_num];
	tex_x = (int)(rc->wall_x * texture->width);
	if (side == 0 && rc->ray.dir.x > 0)
		tex_x = texture->width - tex_x - 1;
	else if (side == 1 && rc->ray.dir.y < 0)
		tex_x = texture->width - tex_x - 1;
	while (rc->start_y < rc->end_y)
	{
		d = rc->start_y * 256 - HEIGHT * 128 + rc->line_height * 128;
		tex_y = ((d * texture->height) / rc->line_height) / 256;
		color = texture->image.pixels[texture->width * tex_y + tex_x];
		if (side == 1)
			color = (color >> 1) & 0x7F7F7F;
		all->image.pixels[rc->start_y * WIDTH + rc->x] = color;
		rc->start_y++;
	}
}

void	draw_wall(t_rchelp *rc, int side, t_wolf3d *all)
{
	double	dist;

	if (side == 0)
	{
		dist = (rc->mapX - rc->ray.origin.x + (1 - rc->stepX) / 2) / rc->ray.dir.x;
		rc->wall_x = rc->ray.origin.y + dist * rc->ray.dir.y;
	}
	else
	{
		dist = (rc->mapY - rc->ray.origin.y + (1 - rc->stepY) / 2) / rc->ray.dir.y;
		rc->wall_x = rc->ray.origin.x + dist * rc->ray.dir.x;
	}
	rc->line_height = (int)(HEIGHT / dist);
	rc->start_y = -rc->line_height / 2 + HEIGHT / 2;
	rc->start_y = rc->start_y < 0 ? 0 : rc->start_y;
	rc->end_y = rc->line_height / 2 + HEIGHT / 2;
	rc->end_y = rc->end_y >= HEIGHT ? HEIGHT - 1 : rc->end_y;
	rc->wall_x -= (int)rc->wall_x;
	if (all->textures_enabled == NO)
		default_wall(side, rc, all);
	else
		textured_wall(side, rc, all);
}