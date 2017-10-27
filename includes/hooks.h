#ifndef HOOKS_H
# define HOOKS_H

# include "wolf3d.h"

int		pressed_hook(int keycode, t_wolf3d *all);
int		released_hook(int keycode, t_wolf3d *all);
int     exit_x(t_wolf3d *param);

#endif
