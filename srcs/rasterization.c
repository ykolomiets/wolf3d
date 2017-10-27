#include "wolf3d.h"

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

void	draw_wall(t_rchelp *rc, int x, int side, int *pixels)
{
	double	dist;
	int		lineHeight;
	t_line	line;
	int 	color;

	if (side == 0)
		dist = (rc->mapX - rc->ray.origin.x + (1 - rc->stepX) / 2) /
			   rc->ray.dir.x;
	else
		dist = (rc->mapY - rc->ray.origin.y + (1 - rc->stepY) / 2) /
			   rc->ray.dir.y;
	lineHeight = (int)(HEIGHT / dist);
	line.p1 = v2(x, -lineHeight / 2 + HEIGHT / 2);
	line.p1.y = line.p1.y < 0 ? 0 : line.p1.y;
	line.p2 = v2(x, lineHeight / 2 + HEIGHT / 2);
	line.p2.y = line.p2.y >= HEIGHT ? HEIGHT - 1 : line.p2.y;
	if (side == 1 && rc->ray.dir.y > 0)
		color = 0xFF1493;
	else if (side == 1)
		color = 0x00FF00;
	else if (side == 0 && rc->ray.dir.x > 0)
		color = 0xFFA500;
	else
		color = 0x00ffff;
	draw_line_dda(&line, pixels, color);
}