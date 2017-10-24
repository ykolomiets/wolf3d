/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_number_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 14:54:30 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 14:54:31 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathx.h"
#include <math.h>

t_cnum	cn_pow(t_cnum *c, double p)
{
	double	r;
	double	phi;
	t_cnum	res;

	r = sqrt(c->r * c->r + c->i * c->i);
	phi = atan2(c->i, c->r);
	r = pow(r, p);
	res.r = r * cos(phi * p);
	res.i = r * sin(phi * p);
	return (res);
}
