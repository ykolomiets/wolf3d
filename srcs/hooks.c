#include "hooks.h"
#include <stdio.h>
#include "camera.h"
#include <stdlib.h>

int		pressed_hook(int keycode, t_wolf3d *all)
{
    printf("keycode: %d\n", keycode);
    if (keycode == 53)
        exit(0);
    else if (keycode == 13)
        cam_move_forward(&all->cam);
    else if (keycode == 1)
        cam_move_backward(&all->cam);
    else if (keycode == 12)
        cam_rotate_right(&all->cam);
    else if (keycode == 14)
        cam_rotate_left(&all->cam);
    else if (keycode == 0)
        cam_move_left(&all->cam);
    else if (keycode == 2)
        cam_move_right(&all->cam);
    else if (keycode == 125)
        cam_zoom_in(&all->cam);
    else if (keycode == 126)
        cam_zoom_out(&all->cam);
    render(all);
    return (0);
}
