#include "hooks.h"
#include "hero.h"
#include <stdlib.h>

int		pressed_hook(int keycode, t_wolf3d *all)
{
    if (keycode == 53)
        exit(0);
    else if (keycode == 13 || keycode == 126)
        hero_move_forward(&all->hero, &all->map);
    else if (keycode == 1 || keycode == 125)
        hero_move_backward(&all->hero, &all->map);
    else if (keycode == 14 || keycode == 124)
        hero_rotate_right(&all->hero);
    else if (keycode == 12|| keycode == 123)
        hero_rotate_left(&all->hero);
    else if (keycode == 0)
        hero_move_left(&all->hero, &all->map);
    else if (keycode == 2)
        hero_move_right(&all->hero, &all->map);
    else if (keycode == 257)
        all->hero.speed = BOOST;
    render(all);
    return (0);
}

int		released_hook(int keycode, t_wolf3d *all)
{
    if (keycode == 257)
        all->hero.speed = DEFAULT;
    return (0);
}

int 	exit_x(t_wolf3d *all)
{
	(void)all;

	exit(0);
}
