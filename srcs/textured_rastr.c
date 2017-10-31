#include "wolf3d.h"
#include <math.h>

static t_vec2	floor_wall_init(int side, t_rchelp *rc)
{
	t_vec2	res;

	if (side == 0 && rc->ray.dir.x > 0)
	{
		res.x = rc->mapX;
		res.y = rc->mapY + rc->wall_x;
	}
	else if (side == 0 && rc->ray.dir.x < 0)
	{
		res.x = rc->mapX + 1.0;
		res.y = rc->mapY + rc->wall_x;
	}
	else if (side == 1 && rc->ray.dir.y > 0)
	{
		res.x = rc->mapX + rc->wall_x;
		res.y = rc->mapY;
	}
	else
	{
		res.x = rc->mapX + rc->wall_x;
		res.y = rc->mapY + 1.0;
	}
	return (res);
}

void			textured_floor(int side, t_rchelp *rc, t_wolf3d *all)
{
	t_vec2		floor_wall;
	t_vec2		cur_floor;
	double		cur_dist;
	t_texture	*texture;
	int 		y;

	floor_wall = floor_wall_init(side, rc);
	texture = &all->textures[TEXTURES_NUM - 1];
	y = rc->end_y - 1;
	while (++y < HEIGHT)
	{
		cur_dist = HEIGHT / (2.0 * y - HEIGHT);
		cur_floor.x = (cur_dist / rc->dist) * floor_wall.x +
					  (1.0 - (cur_dist / rc->dist)) * all->hero.pos.x;
		cur_floor.y = (cur_dist / rc->dist) * floor_wall.y +
					  (1.0 - (cur_dist / rc->dist)) * all->hero.pos.y;
		all->image.pixels[y * WIDTH + rc->x] =
				(texture->image.pixels[texture->width *
									   (((int)(cur_floor.y * texture->height)) % texture->height) +
									   ((int)(cur_floor.x * texture->width)) % texture->width] >> 1) &
				8355711;
	}
}

void			skybox(t_rchelp *rc, t_wolf3d *all)
{
	double		angle;
	int			i;
	t_texture	*skybox_text;

	i = 0;
	angle = (atan2(rc->ray.dir.y, rc->ray.dir.x) + M_PI) / (2 * M_PI);
	skybox_text = &all->skyboxes[all->skybox_num];
	while (i < rc->start_y)
	{
		all->image.pixels[i * WIDTH + rc->x] =
				skybox_text->image.pixels[i * skybox_text->width +
										  (int)(angle * skybox_text->width)];
		i++;
	}
}

void			textured_wall(int side, t_rchelp *rc, t_wolf3d *all)
{
	t_texture	*texture;
	int			tex_x;
	int 		tex_y;
	int 		d;
	int			color;

	texture = &all->textures[rc->tex_num];
	tex_x = (int)(rc->wall_x * texture->width);
	if (side == 0 && rc->ray.dir.x > 0)
		tex_x = texture->width - tex_x - 1;
	else if (side == 1 && rc->ray.dir.y < 0)
		tex_x = texture->width - tex_x - 1;
	while (rc->start_y < rc->end_y)
	{
		d = rc->start_y * 2 - HEIGHT * 1 + rc->line_height * 1;
		tex_y = ((d * texture->height) / rc->line_height) / 2;
		color = texture->image.pixels[texture->width * tex_y + tex_x];
		if (side == 1)
			color = (color >> 1) & 0x7F7F7F;
		all->image.pixels[rc->start_y * WIDTH + rc->x] = color;
		rc->start_y++;
	}
}