/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 03:25:42 by youncho           #+#    #+#             */
/*   Updated: 2021/02/23 19:43:58 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_exit(char *str)
{
	ft_putstr_fd("[ERROR] ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}

int		check_extension(char *s, char *ex)
{
	return (!ft_strncmp(s + ft_strlen(s) - ft_strlen(ex), ex, ft_strlen(ex)));
}

int		isdigit_str(char *str)
{
	size_t i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[++i]))
			return (0);
	return (1);
}

void	deallocation_2d(char **arr)
{
	size_t i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
