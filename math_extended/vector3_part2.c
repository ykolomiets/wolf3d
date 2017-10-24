/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:17:38 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 10:17:40 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathx.h"
#include <math.h>

double	v3_dot(t_vec3 a, t_vec3 b)
{
	double	res;

	res = a.x * b.x + a.y * b.y + a.z * b.z;
	return (res);
}

t_vec3	v3_cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

double	v3_magnitude(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	v3_normalize(t_vec3 v)
{
	double	magnitude;

	magnitude = v3_magnitude(v);
	if (fabs(magnitude) > 0.00005)
	{
		v.x /= magnitude;
		v.y /= magnitude;
		v.z /= magnitude;
	}
	return (v);
}
