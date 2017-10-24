/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 18:04:02 by ykolomie          #+#    #+#             */
/*   Updated: 2017/04/20 16:18:59 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*expand_buf(char *buf, unsigned int *size)
{
	char			*new_buf;
	unsigned int	i;

	new_buf = malloc(sizeof(char) * (*size) * 2);
	i = 0;
	while (i < *size)
	{
		new_buf[i] = buf[i];
		i++;
	}
	*size *= 2;
	free(buf);
	return (new_buf);
}

char	*read_file(int fd)
{
	char			*buf;
	unsigned int	length;
	unsigned int	buf_size;
	int				readed;

	length = 0;
	buf_size = 16;
	buf = malloc(sizeof(char) * buf_size);
	while ((readed = read(fd, buf + length, buf_size - length)))
	{
		length += readed;
		if (length == buf_size)
			buf = expand_buf(buf, &buf_size);
	}
	buf[length] = '\0';
	return (buf);
}
