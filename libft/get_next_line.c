/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:46:05 by ykolomie          #+#    #+#             */
/*   Updated: 2017/04/20 14:53:57 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_strunit(char **first, char **second)
{
	char *result;

	result = ft_strjoin(*first, *second);
	ft_strdel(first);
	ft_strdel(second);
	return (result);
}

void		gnl_main(t_fd_story *mfd, char **line, int *ret)
{
	char	*temp_str;
	char	*term;

	*ret = 0;
	while (mfd->st || (mfd->read = read(mfd->fd, mfd->buf, BUFF_SIZE)) > 0)
	{
		*ret = 1;
		if ((term = ft_memchr(mfd->buf + mfd->st, '\n', mfd->read - mfd->st)) ||
			(term = ft_memchr(mfd->buf + mfd->st, '\0', mfd->read - mfd->st)))
		{
			temp_str = ft_strsub(mfd->buf, mfd->st, term - mfd->buf - mfd->st);
			*line = ft_strunit(line, &temp_str);
			mfd->st = (term - mfd->buf + 1 >= mfd->read ?
								0 : term - mfd->buf + 1);
			break ;
		}
		else
		{
			temp_str = ft_strsub(mfd->buf, mfd->st, mfd->read - mfd->st);
			*line = ft_strunit(line, &temp_str);
			mfd->st = 0;
		}
	}
}

t_list		*ft_lstnew_fd(int fd)
{
	t_list	*res;

	res = (t_list*)malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = malloc(sizeof(t_fd_story));
	if (!res->content)
	{
		free(res);
		return (NULL);
	}
	((t_fd_story *)res->content)->fd = fd;
	((t_fd_story *)res->content)->st = 0;
	((t_fd_story *)res->content)->read = 0;
	res->content_size = sizeof(t_fd_story);
	res->next = NULL;
	return (res);
}

t_fd_story	*find_mfd(t_list **head, int fd)
{
	t_list	*current_node;

	current_node = *head;
	while (current_node)
	{
		if (((t_fd_story *)current_node->content)->fd == fd)
			return ((t_fd_story *)current_node->content);
		current_node = current_node->next;
	}
	ft_lstadd(head, ft_lstnew_fd(fd));
	return ((t_fd_story *)(*head)->content);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*head = NULL;
	int				ret;
	t_fd_story		*mfd;

	if (fd == -1 || !line)
		return (-1);
	mfd = find_mfd(&head, fd);
	*line = ft_strnew(0);
	gnl_main(mfd, line, &ret);
	return (mfd->read == -1 ? -1 : ret);
}
