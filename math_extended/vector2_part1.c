/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:12:11 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 10:12:12 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mathx.h"
#include <stdlib.h>

t_vec2	v2_create(double x, double y)
{
	return (t_vec2){x, y};
}

t_vec2	v2_add(t_vec2 a, t_vec2 b)
{
	return (t_vec2){a.x + b.x, a.y + b.y};
}

t_vec2	v2_sub(t_vec2 a, t_vec2 b)
{
	return (t_vec2){a.x - b.x, a.y - b.y};
}
