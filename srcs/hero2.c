#include "hero.h"

void            hero_rotate_left(t_hero *hero)
{
	static t_matrix2    rotation_matrix = {
			0.999657324975557,
			0.026176948307873,
			-0.026176948307873,
			0.999657324975557
	};
	static t_matrix2    rotation_matrix_2x = {
			0.998629534754574,
			0.052335956242944,
			-0.052335956242944,
			0.998629534754574
	};

	if (hero->speed == BOOST)
		hero->dir = m2_mult_v2(rotation_matrix_2x, hero->dir);
	else
		hero->dir = m2_mult_v2(rotation_matrix, hero->dir);
}

void            hero_rotate_right(t_hero *hero)
{
	static t_matrix2    rotation_matrix = {
			0.999657324975557,
			-0.026176948307873,
			0.026176948307873,
			0.999657324975557
	};
	static t_matrix2    rotation_matrix_2x = {
			0.998629534754574,
			-0.052335956242944,
			0.052335956242944,
			0.998629534754574
	};

	if (hero->speed == BOOST)
		hero->dir = m2_mult_v2(rotation_matrix_2x, hero->dir);
	else
		hero->dir = m2_mult_v2(rotation_matrix, hero->dir);
}
