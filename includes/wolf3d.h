#ifndef WOLF3D_H
# define WOLF3D_H

# include "hero.h"
# include "map.h"

# define WIDTH 1024
# define HEIGHT 768

typedef struct  s_image
{
    void        *image;
    int         *pixels;
    int         bpp;
    int         sl;
    int         endian;
}               t_image;

typedef struct  s_wolf3d
{
    void        *mlx;
    void        *win;
    t_image     image;
    t_hero		hero;
    t_map       map;
}               t_wolf3d;

int     wolf3d(char *file_name);
void	render(t_wolf3d *all);

#endif
