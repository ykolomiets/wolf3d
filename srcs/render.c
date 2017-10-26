#include "wolf3d.h"
#include "mlx.h"
#include "ray_casting.h"
#include <math.h>
#include <pthread.h>

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

void	prepare_ray_casting(t_rchelp *rc, int x, t_hero *hero)
{
	double planeCoord;

	planeCoord = 2 * x / (double)WIDTH - 1;
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
			break;
	}
	return (side);
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
		color = 0x0000ff;
	else if (side == 1)
		color = 0x00ff00;
	else if (side == 0 && rc->ray.dir.x > 0)
		color = 0xff0000;
	else
		color = 0x00ffff;
	draw_line_dda(&line, pixels, color);
}

void	*render_part(void *param)
{
	t_param		*p;
	int			i;
	t_rchelp	rc;
	int 		side;

	p = (t_param *)param;
	i = p->thread_num;
	while (i < WIDTH)
	{
		prepare_ray_casting(&rc, i, &p->all->hero);
		side = ray_casting(&rc, &p->all->map);
		draw_wall(&rc, i, side, p->all->image.pixels);
		i += NUM_THREADS;
	}
	pthread_exit(NULL);
}

void	render(t_wolf3d *all)
{

	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	t_param params[NUM_THREADS];
	int i;
	void *res;

	fill_floor_ceil(all->image.pixels);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	i = -1;
	while (++i < NUM_THREADS)
	{
		params[i].thread_num = i;
		params[i].all = all;
		pthread_create(&threads[i], &attr, render_part, &params[i]);
	}
	pthread_attr_destroy(&attr);
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], &res);
	mlx_put_image_to_window(all->mlx, all->win, all->image.image, 0, 0);
}