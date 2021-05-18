/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:07:22 by youncho           #+#    #+#             */
/*   Updated: 2021/05/17 14:52:29 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_check_row(t_cub3d *cub)
{
	int	i;
	int	j;
	int	is_inside;

	i = -1;
	while (++i < cub->map_height)
	{
		j = -1;
		is_inside = 0;
		while (++j < cub->map_width)
		{
			if (!is_inside && cub->map[i][j] == '1')
				is_inside = 1;
			else if (!is_inside && ft_strchr("NEWS0", cub->map[i][j]))
				error_exit("Map Error");
			else if (is_inside && cub->map[i][j] == ' ')
			{
				is_inside = 0;
				error_handler(cub->map[i][j - 1] != '1', 6);
			}
		}
		error_handler(!ft_strchr("1 ", cub->map[i][j - 1]), 6);
	}
}

void	map_check_col(t_cub3d *cub)
{
	int	i;
	int	j;
	int	is_inside;

	j = -1;
	while (++j < cub->map_width)
	{
		i = -1;
		is_inside = 0;
		while (++i < cub->map_height)
		{
			if (!is_inside && cub->map[i][j] == '1')
				is_inside = 1;
			else if (!is_inside && ft_strchr("NEWS0", cub->map[i][j]))
				error_exit("Map Error");
			else if (is_inside && cub->map[i][j] == ' ')
			{
				is_inside = 0;
				error_handler(cub->map[i - 1][j] != '1', 6);
			}
		}
		error_handler(ft_strchr("NEWS0", cub->map[i - 1][j]), 6);
	}
}

void	check_valid(t_cub3d *cub)
{
	error_handler(!cub->screen_width || !cub->screen_height
		|| !cub->tex.path[0] || !cub->tex.path[1]
		|| !cub->tex.path[2] || !cub->tex.path[3]
		|| !cub->tex.path[4] || cub->tex.rgb[0] == -1
		|| cub->tex.rgb[1] == -1, 4);
	error_handler(!cub->map_width || !cub->map_height
		|| !cub->cam.dir || !cub->cam.x || !cub->cam.y, 5);
	map_check_row(cub);
	map_check_col(cub);
}

int		check_extension(char *s, char *ex)
{
	return (!ft_strncmp(s + ft_strlen(s) - ft_strlen(ex), ex, ft_strlen(ex)));
}

int		isdigit_str(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
