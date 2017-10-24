/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_2d_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:56:29 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 10:56:30 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_malloc_2d_array(int rows, int columns, int elem_size)
{
	void	**res;

	res = malloc(sizeof(void*) * rows);
	while (rows--)
		res[rows] = malloc(elem_size * columns);
	return ((void *)res);
}
