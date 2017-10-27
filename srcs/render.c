#include "wolf3d.h"
#include "mlx.h"
#include <math.h>
#include <pthread.h>

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