#ifndef HERO_H
# define HERO_H

# include "mathx.h"

# define MOVE_SPEED     	0.03

# define BOOST		2
# define DEFAULT	1

typedef struct	s_hero
{
	t_vec2	pos;
	t_vec2	dir;
	int 	speed;
	double 	zoom;
}				t_hero;

void			hero_rotate_left(t_hero *hero);
void			hero_rotate_right(t_hero *hero);
void			hero_move_forward(t_hero *hero);
void			hero_move_backward(t_hero *hero);
void			hero_move_left(t_hero *hero);
void			hero_move_right(t_hero *hero);
void			hero_zoom_in(t_hero *hero);
void			hero_zoom_out(t_hero *hero);

#endif
