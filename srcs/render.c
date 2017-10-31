#include "wolf3d.h"
#include "mlx.h"
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
		rc.x = i;
		prepare_ray_casting(&rc, &p->all->hero);
		side = ray_casting(&rc, &p->all->map);
		draw_strip(&rc, side, p->all);
		i += NUM_THREADS;
	}
	pthread_exit(NULL);
}

void	display_help(t_wolf3d *all)
{
	int i;

	i = -1;
	PUT_STR(++i * 18, "*----------- HELP -----------*");
	PUT_STR(++i * 18, "|  W / (up) - move forward   |");
	PUT_STR(++i * 18, "|  S / (down) - move back    |");
	PUT_STR(++i * 18, "|  Q / (left) - rotate left  |");
	PUT_STR(++i * 18, "| E / (right) - rotate right |");
	PUT_STR(++i * 18, "|      A - move left         |");
	PUT_STR(++i * 18, "|      D - move right        |");
	PUT_STR(++i * 18, "|     Shift - speed up       |");
	PUT_STR(++i * 18, "|             ****           |");
	PUT_STR(++i * 18, "|    T - enable textures     |");
	PUT_STR(++i * 18, "|    Tab - change skybox     |");
	PUT_STR(++i * 18, "*----------------------------*");
}

void	render(t_wolf3d *all)
{

	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	t_param params[NUM_THREADS];
	int i;
	void *res;

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
	if (all->help_display)
		display_help(all);
}