#include "wolf3d.h"
#include "mlx.h"
#include "hooks.h"
#include <stdio.h>

void		textures_loading(t_texture *textures, void *mlx)
{
	static char	*file_names[TEXTURES_NUM] = {"resources/xpm_textures/bluestone.xpm",
												"resources/xpm_textures/eagle.xpm",
												"resources/xpm_textures/greystone.xpm",
												"resources/xpm_textures/mossy.xpm",
												"resources/xpm_textures/redbrick.xpm",
												"resources/xpm_textures/wood.xpm",
												"resources/xpm_textures/colorstone.xpm"
	};
	int 		i;

	i = -1;
	while (++i < TEXTURES_NUM)
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

void		skyboxes_loading(t_texture *skyboxes, void *mlx)
{
	static char	*file_names[2] = {"resources/xpm_textures/stars1.xpm",
									 "resources/xpm_textures/stars2.xpm",};
	int 		i;

	i = -1;
	while (++i < 2)
	{
		skyboxes[i].image.image = mlx_xpm_file_to_image(mlx,
														file_names[i],
														&skyboxes[i].width,
														&skyboxes[i].height);
		skyboxes[i].image.pixels =
				(int *)mlx_get_data_addr(skyboxes[i].image.image,
										 &skyboxes[i].image.bpp,
										 &skyboxes[i].image.sl,
										 &skyboxes[i].image.endian);
	}
}

static int  init_wolf(t_wolf3d *all)
{
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, WIDTH, HEIGHT, "Wolf3D");
    all->image.image = mlx_new_image(all->mlx, WIDTH, HEIGHT);
    all->image.pixels = (int *)mlx_get_data_addr(all->image.image, &all->image.bpp,
    &all->image.sl, &all->image.endian);
	printf("start loading\n");
	skyboxes_loading(all->skyboxes, all->mlx);
	printf("skybox loaded\n");
	textures_loading(all->textures, all->mlx);
	printf("textures loaded\n");
	all->skybox_num = 0;
	all->textures_enabled = NO;
	all->actions = (t_action_set){NO, NO, NO, NO, NO, NO};
	music_on();
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

int     wolf3d(char *file_name)
{
    t_wolf3d    all;

    if (!init_wolf(&all))
    {
        if (!read_map(file_name, &all.map, &all.hero))
        {
			all.hero.dir = v2(0, 1);
            all.hero.speed = DEFAULT;
			run(&all);
            return (0);
        }
    }
    return (1);
}