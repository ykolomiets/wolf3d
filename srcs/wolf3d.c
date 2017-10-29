#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"
#include "hooks.h"
#include <stdio.h>

void		textures_loading(t_texture *textures, void *mlx)
{
	static char	*file_names[] = {"xpm_textures/greystone.xpm",
									"xpm_textures/mossy.xpm",
									"xpm_textures/redbrick.xpm",
									"xpm_textures/eagle.xpm",
									"xpm_textures/colorstone.xpm"};
	int 		i;

	i = -1;
	while (++i < 5)
	{
		textures[i].image.image = mlx_xpm_file_to_image(mlx,
														file_names[i],
														&textures[i].width,
														&textures[i].height);
		textures[i].image.pixels =
				(int *)mlx_get_data_addr(textures[i].image.image,
										 &textures[i].image.bpp,
										 &textures[i].image.sl,
										 &textures[i].image.endian);
	}
}

static int  init_wolf(t_wolf3d *all)
{
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, WIDTH, HEIGHT, "Wolf3D");
    all->image.image = mlx_new_image(all->mlx, WIDTH, HEIGHT);
    all->image.pixels = (int *)mlx_get_data_addr(all->image.image, &all->image.bpp,
    &all->image.sl, &all->image.endian);
	textures_loading(all->textures, all->mlx);
	all->textures_enabled = NO;
	all->actions = (t_action_set){NO, NO, NO, NO, NO, NO};
    return (0);
}

static void	run(t_wolf3d *all)
{
    mlx_hook(all->win, 2, 0, pressed_hook, all);
	mlx_hook(all->win, 3, 0, released_hook, all);
	mlx_hook(all->win, 17, 0, exit_x, all);
	mlx_loop_hook(all->mlx, loop_hook, all);
	mlx_loop(all->mlx);
}

void	print_map(t_map *map)
{
	printf("MAP %d x %d\n", map->rows, map->cols);
	for (int i = 0; i < map->rows; i++)
	{
		for (int j = 0; j < map->cols; j++)
		{
			printf("%d ", map->walls[i][j]);
		}
		printf("\n");
	}
	printf("-------------------\n");
}

int     wolf3d(char *file_name)
{
    t_wolf3d    all;

    if (!init_wolf(&all))
    {
        if (!read_map(file_name, &all.map, &all.hero))
        {
			print_map(&all.map);
			all.hero.dir = v2(0, 1);
			printf("hero.pos = (%f, %f), dir = (%f, %f)\n", all.hero.pos.x, all.hero.pos.y, all.hero.dir.x, all.hero.dir.y);
            all.hero.speed = DEFAULT;
			run(&all);
            return (0);
        }
    }
    return (1);
}