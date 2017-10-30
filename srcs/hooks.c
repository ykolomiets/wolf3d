#include "hooks.h"
#include "hero.h"
#include <stdlib.h>
#include <stdio.h>

static int	pressed_hook2(int keycode, t_wolf3d *all)
{
	if (keycode == 14 || keycode == 124)
	{
		all->actions.rotate_left = NO;
		all->actions.rotate_right = YES;
	}
	else if (keycode == 12|| keycode == 123)
	{
		all->actions.rotate_left = YES;
		all->actions.rotate_right = NO;
	}
	else if (keycode == 257)
		all->hero.speed = BOOST;
	return (0);
}

int			pressed_hook(int keycode, t_wolf3d *all)
{
    if (keycode == 13 || keycode == 126)
	{
		all->actions.move_forward = YES;
		all->actions.move_backward = NO;
	}
    else if (keycode == 1 || keycode == 125)
	{
		all->actions.move_forward = NO;
		all->actions.move_backward = YES;
	}
    else if (keycode == 0)
	{
		all->actions.move_left = YES;
		all->actions.move_right = NO;
	}
    else if (keycode == 2)
	{
		all->actions.move_left = NO;
		all->actions.move_right = YES;
	}
	else
		pressed_hook2(keycode, all);
    return (0);
}

int			released_hook(int keycode, t_wolf3d *all)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 13 || keycode == 126)
		all->actions.move_forward = NO;
	else if (keycode == 1 || keycode == 125)
		all->actions.move_backward = NO;
	else if (keycode == 14 || keycode == 124)
		all->actions.rotate_right = NO;
	else if (keycode == 12|| keycode == 123)
		all->actions.rotate_left = NO;
	else if (keycode == 0)
		all->actions.move_left = NO;
	else if (keycode == 2)
		all->actions.move_right = NO;
	else if (keycode == 257)
		all->hero.speed = DEFAULT;
	else if (keycode == 53)
		exit(0);
	else if (keycode == 17)
		all->textures_enabled = all->textures_enabled ? NO : YES;
	else if (keycode == 48)
		all->skybox_num = (all->skybox_num + 1) % 2;
	return (0);
}

int			loop_hook(t_wolf3d *all)
{
	if (all->actions.move_forward)
		hero_move_forward(&all->hero, &all->map);
	else if (all->actions.move_backward)
		hero_move_backward(&all->hero, &all->map);
	if (all->actions.rotate_right)
		hero_rotate_right(&all->hero);
	else if (all->actions.rotate_left)
		hero_rotate_left(&all->hero);
	if (all->actions.move_left)
		hero_move_left(&all->hero, &all->map);
	else if (all->actions.move_right)
		hero_move_right(&all->hero, &all->map);
	render(all);
	return (0);
}

int			exit_x(t_wolf3d *all)
{
	(void)all;

	exit(0);
}
