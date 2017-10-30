#include "wolf3d.h"

void	default_wall(int side, t_rchelp *rc, t_wolf3d *all)
{
	int		color;
	int 	i;

	if (side == 1 && rc->ray.dir.y > 0)
		color = 0xFF1493;
	else if (side == 1)
		color = 0x00FF00;
	else if (side == 0 && rc->ray.dir.x > 0)
		color = 0xFFA500;
	else
		color = 0x00ffff;
	i = 0;
	while (i < rc->start_y)
		all->image.pixels[i++ * WIDTH + rc->x] = 0x87cefa;
	while (i < rc->end_y)
		all->image.pixels[i++ * WIDTH + rc->x] = color;
	while (i < HEIGHT)
		all->image.pixels[i++ * WIDTH + rc->x] = 0x8B4513;
}

t_vec2	floor_wall_init(int side, t_rchelp *rc)
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

void	textured_floor(int side, t_rchelp *rc, t_wolf3d *all)
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

void	textured_wall(int side, t_rchelp *rc, t_wolf3d *all)
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
	textured_floor(side, rc, all);
}

void	draw_wall(t_rchelp *rc, int side, t_wolf3d *all)
{
	if (side == 0)
	{
		rc->dist = (rc->mapX - rc->ray.origin.x + (1 - rc->stepX) / 2) / rc->ray.dir.x;
		rc->wall_x = rc->ray.origin.y + rc->dist * rc->ray.dir.y;
	}
	else
	{
		rc->dist = (rc->mapY - rc->ray.origin.y + (1 - rc->stepY) / 2) / rc->ray.dir.y;
		rc->wall_x = rc->ray.origin.x + rc->dist * rc->ray.dir.x;
	}
	rc->line_height = (int)(HEIGHT / rc->dist);
	rc->start_y = -rc->line_height / 2 + HEIGHT / 2;
	rc->start_y = rc->start_y < 0 ? 0 : rc->start_y;
	rc->end_y = rc->line_height / 2 + HEIGHT / 2;
	rc->end_y = rc->end_y >= HEIGHT ? HEIGHT - 1 : rc->end_y;
	rc->wall_x -= (int)rc->wall_x;
	if (all->textures_enabled == NO)
		default_wall(side, rc, all);
	else
		textured_wall(side, rc, all);
}