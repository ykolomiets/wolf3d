/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 10:57:14 by ykolomie          #+#    #+#             */
/*   Updated: 2017/09/30 10:57:15 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_2d_array(void ***arr, int rows)
{
	int i;

	i = 0;
	while (i < rows)
		free((*arr)[i++]);
	free((*arr));
	*arr = 0;
}
