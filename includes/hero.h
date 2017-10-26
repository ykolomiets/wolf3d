#ifndef HERO_H
# define HERO_H

# include "wolf3d.h"

void			hero_rotate_left(t_hero *hero);
void			hero_rotate_right(t_hero *hero);
void			hero_move_forward(t_hero *hero, t_map *map);
void			hero_move_backward(t_hero *hero, t_map *map);
void			hero_move_left(t_hero *hero, t_map *map);
void			hero_move_right(t_hero *hero, t_map *map);

#endif
