/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:12:30 by youncho           #+#    #+#             */
/*   Updated: 2021/05/16 00:20:16 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			set_line_size(char **line, size_t len)
{
	char	*tmp;
	size_t	i;

	tmp = malloc(BUFFER_SIZE + len + 1);
	if (!tmp)
		return (FAILURE);
	i = -1;
	while (++i < len)
		tmp[i] = (*line)[i];
	tmp[i] = (char)0;
	free(*line);
	*line = tmp;
	return (SUCCESS);
}

t_storage	*get_new_node(int fd)
{
	t_storage	*ret;

	ret = malloc(sizeof(t_storage));
	if (!ret)
		return (FAILURE);
	ret->fd = fd;
	ret->next = (t_storage *)0;
	ret->buff[0] = (char)0;
	return (ret);
}

t_storage	*get_current_node(int fd, t_storage *node)
{
	while (node->fd != fd)
	{
		if (!node->next)
			return (node->next = get_new_node(fd));
		node = node->next;
	}
	return (node);
}

int			deallocation(int fd, t_storage **head, int ret)
{
	t_storage	*prev;
	t_storage	*del;

	prev = *head;
	while (prev->next && prev->next->fd != fd)
		prev = prev->next;
	del = get_current_node(fd, *head);
	if ((*head)->fd == fd)
		*head = del->next;
	else
		prev->next = del->next;
	free(del);
	return (ret);
}
