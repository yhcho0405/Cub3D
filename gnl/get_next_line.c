/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 17:12:27 by youncho           #+#    #+#             */
/*   Updated: 2021/05/16 00:49:07 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	make_line(char **line, char *buffer, int i)
{
	int	ret;
	int	j;

	j = 0;
	ret = 0;
	(*line)[i++] = buffer[j];
	while ((*line)[i - 1])
	{
		if (buffer[j++] == '\n')
		{
			(*line)[--i] = (char)0;
			ret = 1;
			break ;
		}
		(*line)[i++] = buffer[j];
	}
	i = 0;
	while (buffer[j])
		buffer[i++] = buffer[j++];
	buffer[i] = (char)0;
	return (ret);
}

int	read_control(int fd, char **line, char *buffer)
{
	int	len;
	int	ret;
	int	i;

	len = 1;
	if (read(fd, buffer, 0) == R_ERR)
		return (R_ERR);
	while (len > 0)
	{
		i = ft_strlen(*line);
		if (!(set_line_size(line, i)))
			return (R_ERR);
		ret = make_line(line, buffer, i);
		if (ret)
			return (ret);
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == R_ERR)
			return (R_ERR);
		buffer[len] = 0;
	}
	return (R_EOF);
}

int	gnl_init(int fd, char **line, t_storage **head, t_storage **curr)
{
	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (FAILURE);
	if (!*head)
	{
		*head = get_new_node(fd);
		if (!*head)
			return (FAILURE);
	}
	*curr = get_current_node(fd, *head);
	if (!*curr)
		return (deallocation(fd, head, FAILURE));
	*line = (char *)0;
	return (SUCCESS);
}

int	get_next_line(int fd, char **line)
{
	static t_storage	*head;
	t_storage			*curr;
	int					ret;

	if (gnl_init(fd, line, &head, &curr) == FAILURE)
		return (R_ERR);
	ret = read_control(fd, line, curr->buff);
	if (!ret)
		return (deallocation(fd, &head, R_EOF));
	if (ret == R_ERR)
		return (deallocation(fd, &head, R_ERR));
	else
		return (R_NL);
}
