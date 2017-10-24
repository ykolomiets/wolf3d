/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:15:32 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 10:15:33 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathx.h"
#include <math.h>

t_vec2		v2_mult_by_scalar(t_vec2 a, double c)
{
	a.x *= c;
	a.y *= c;
	return (a);
}

t_vec2		v2_div_by_scalar(t_vec2 a, double c)
{
	if (fabs(c) < 0.00005)
		return (a);
	a.x *= c;
	a.y *= c;
	return (a);
}

double	v2_dot_product(t_vec2 a, t_vec2 b)
{
	double	res;

	res = a.x * b.x + a.y * b.y;
	return (res);
}

double	v2_magnitude(t_vec2 a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_vec2	v2_normalize(t_vec2 a)
{
	double	magnitude;

	magnitude = v2_magnitude(a);
	if (fabs(magnitude) > 0.00005)
	{
		a.x /= magnitude;
		a.y /= magnitude;
	}
	return (a);
}
