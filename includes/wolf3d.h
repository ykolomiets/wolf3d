#ifndef WOLF3D_H
# define WOLF3D_H

# include "mathx.h"
# include "ray_casting.h"

# define WIDTH			1024
# define HEIGHT			768
# define NUM_THREADS	8

# define MOVE_SPEED		0.03
# define BOOST			2
# define DEFAULT		1


typedef struct  s_image
{
    void        *image;
    int         *pixels;
    int         bpp;
    int         sl;
    int         endian;
}               t_image;

typedef struct  s_map
{
	int     rows;
	int     cols;
	int     **walls;
}               t_map;

typedef struct	s_hero
{
	t_vec2	pos;
	t_vec2	dir;
	int 	speed;
}				t_hero;

typedef struct  s_wolf3d
{
    void        *mlx;
    void        *win;
    t_image     image;
    t_hero		hero;
    t_map       map;
}               t_wolf3d;

typedef struct	s_param
{
	int				thread_num;
	t_wolf3d		*all;
}				t_param;

typedef struct	s_rchelp
{
	t_ray		ray;
	t_vec2		sideDist;
	t_vec2		deltaDist;
	int 		stepX;
	int			stepY;
	int			mapX;
	int 		mapY;
}				t_rchelp;

int     wolf3d(char *file_name);
void	render(t_wolf3d *all);
int		read_map(char *map_file, t_map *map, t_hero *hero);


#endif
