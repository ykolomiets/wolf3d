#include "wolf3d.h"
#include "mlx.h"
#include "libft.h"

static int  init_wolf(t_wolf3d *all)
{
    all->mlx = mlx_init();
    all->win = mlx_new_window(all->mlx, WIDTH, HEIGHT, "Wolf3D");
    all->image.image = mlx_new_image(all->mlx, WIDTH, HEIGHT);
    all->image.pixels = (int *)mlx_get_data_addr(all->image.image, &all->image.bpp,
    &all->image.sl, &all->image.endian);
    return (0);
}

int     wolf3d(char *file_name)
{
    t_wolf3d    all;

    if (!init_wolf(&all))
    {
        ft_putendl("mlx inited");
        if (!read_map(file_name, &all.map, &all.cam))
        {
            ft_putendl("All is fine");
            return (0);
        }
        return (1);
            //run_game(&all);
    }
    return (1);
}