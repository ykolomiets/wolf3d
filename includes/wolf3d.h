#ifndef WOLF3D_H
# define WOLF3D_H

# include "mathx.h"

# define WIDTH			1600
# define HEIGHT			900
# define NUM_THREADS	8

# define TEXTURES_NUM	7

# define MOVE_SPEED		0.03
# define BOOST			2
# define DEFAULT		1

# define YES			1
# define NO				0


typedef struct  s_image
{
    void        *image;
    int         *pixels;
    int         bpp;
    int         sl;
    int         endian;
}               t_image;

typedef	struct	s_texture
{
	t_image		image;
	int			width;
	int			height;
}				t_texture;

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

typedef struct	s_action_set
{
	int			move_forward;
	int			move_backward;
	int			move_right;
	int			move_left;
	int			rotate_right;
	int 		rotate_left;
}				t_action_set;

typedef struct  s_wolf3d
{
    void        	*mlx;
    void        	*win;
    t_image     	image;
    t_hero			hero;
    t_map       	map;
	t_texture		textures[TEXTURES_NUM];
	int				textures_enabled;
	t_action_set	actions;

}               t_wolf3d;

typedef struct	s_param
{
	int				thread_num;
	t_wolf3d		*all;
}				t_param;

typedef struct  s_ray
{
	t_vec2      origin;
	t_vec2      dir;
}               t_ray;

typedef struct	s_line
{
	t_vec2		p1;
	t_vec2		p2;
}				t_line;

typedef struct	s_rchelp
{
	int			x;
	t_ray		ray;
	t_vec2		sideDist;
	t_vec2		deltaDist;
	int 		stepX;
	int			stepY;
	int			mapX;
	int 		mapY;
	int			tex_num;
	double		wall_x;
	double 		dist;
	int			line_height;
	int			start_y;
	int 		end_y;
}				t_rchelp;

int     		wolf3d(char *file_name);
int             read_map(char *file, t_map *map, t_hero *hero);
void			render(t_wolf3d *all);
int				ray_casting(t_rchelp *rc, t_map *map);
void			prepare_ray_casting(t_rchelp *rc, t_hero *hero);
void			assign_step_and_sideDist(t_rchelp *rc);
void			draw_wall(t_rchelp *rc, int side, t_wolf3d *all);
void 			put_error(int error_code);

#endif
