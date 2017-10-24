#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# include "mathx.h"

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

#endif
