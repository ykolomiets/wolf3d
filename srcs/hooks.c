#include "hooks.h"
#include <stdio.h>
#include "hero.h"
#include <stdlib.h>

int		pressed_hook(int keycode, t_wolf3d *all)
{
    printf("keycode: %d\n", keycode);
    if (keycode == 53)
        exit(0);
    else if (keycode == 13)
        hero_move_forward(&all->hero);
    else if (keycode == 1)
        hero_move_backward(&all->hero);
    else if (keycode == 12)
        hero_rotate_right(&all->hero);
    else if (keycode == 14)
        hero_rotate_left(&all->hero);
    else if (keycode == 0)
        hero_move_left(&all->hero);
    else if (keycode == 2)
        hero_move_right(&all->hero);
    else if (keycode == 125)
        hero_zoom_in(&all->hero);
    else if (keycode == 126)
        hero_zoom_out(&all->hero);
    render(all);
    return (0);
}
