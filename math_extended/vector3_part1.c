/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:16:26 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 10:16:42 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathx.h"
#include <math.h>

t_vec3	v3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vec3	v3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}

t_vec3	v3_mult_c(t_vec3 a, double c)
{
	a.x *= c;
	a.y *= c;
	a.z *= c;
	return (a);
}

t_vec3	v3_div_by_scalar(t_vec3 a, double c, int *err)
{
	if (fabs(c) < 0.00005)
		*err = 1;
	else
	{
		a.x /= c;
		a.y /= c;
		a.z /= c;
		*err = 0;
	}
	return (a);
}
