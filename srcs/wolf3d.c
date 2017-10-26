#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"
#include "hooks.h"

static int  init_wolf(t_wolf3d *all)
{
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, WIDTH, HEIGHT, "Wolf3D");
    all->image.image = mlx_new_image(all->mlx, WIDTH, HEIGHT);
    all->image.pixels = (int *)mlx_get_data_addr(all->image.image, &all->image.bpp,
    &all->image.sl, &all->image.endian);
    return (0);
}

static void	run(t_wolf3d *all)
{
    render(all);
    mlx_hook(all->win, 2, 0, pressed_hook, all);
	mlx_loop(all->mlx);
}

int     wolf3d(char *file_name)
{
    t_wolf3d    all;

    if (!init_wolf(&all))
    {
        ft_putendl("mlx inited");
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