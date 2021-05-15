/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 03:25:42 by youncho           #+#    #+#             */
/*   Updated: 2021/05/15 12:28:07 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_check(t_cub3d *cub)
{
	int i;
	int j;
	int is_inside;

	i = -1;
	while (++i < cub->map_height && (j = -1) && !(is_inside = 0))
	{
		while (++j < cub->map_width)
			if (!is_inside && cub->map[i][j] == '1')
				is_inside = 1;
			else if (!is_inside && ft_strchr("NEWS0", cub->map[i][j]))
				error_exit("Map Error");
			else if (is_inside && cub->map[i][j] == ' ' && !(is_inside = 0))
				_err(cub->map[i][j - 1] != '1', 6);
		_err(ft_strchr("NEWS0", cub->map[i][j - 1]), 6);
	}
	j = -1;
	while (++j < cub->map_width && (i = -1) && !(is_inside = 0))
	{
		while (++i < cub->map_height)
			if (!is_inside && cub->map[i][j] == '1')
				is_inside = 1;
			else if (!is_inside && ft_strchr("NEWS0", cub->map[i][j]))
				error_exit("Map Error");
			else if (is_inside && cub->map[i][j] == ' ' && !(is_inside = 0))
				_err(cub->map[i - 1][j] != '1', 6);
		_err(ft_strchr("NEWS0", cub->map[i - 1][j]), 6);
	}
}

void check_valid(t_cub3d *cub)
{
	_err(!cub->screen_width || !cub->screen_height ||
		!cub->tex.path[0] || !cub->tex.path[1] ||
		!cub->tex.path[2] || !cub->tex.path[3] ||
		!cub->tex.path[4] || cub->tex.rgb[0] == -1 ||
		cub->tex.rgb[1] == -1, 4);
	_err(!cub->map_width || !cub->map_height ||
		!cub->cam.dir || !cub->cam.x || !cub->cam.y, 5);
	map_check(cub);
}


void	error_exit(char *str)
{
	ft_putstr_fd("[ERROR] ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}

void	_err(bool err, int code)
{
	if (!err)
		return ;
	if (code == 1)
		error_exit("Allocation Fail");
	else if (code == 2)
		error_exit("Map Element Wrong");
	else if (code == 3)
		error_exit("Multiple Player Error");
	else if (code == 4)
		error_exit("Info Field Error");
	else if (code == 5)
		error_exit("Map Field Error");
	else if (code == 6)
		error_exit("Map Error");
	else if (code == 7)
		error_exit("open() Fail");
	else if (code == 8)
		error_exit("Allocation Fail");
	else if (code == 9)
		error_exit("Allocation Fail");
	else if (code == 10)
		error_exit("Allocation Fail");
	else if (code == 11)
		error_exit("Allocation Fail");
	else if (code == 12)
		error_exit("Allocation Fail");
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
		if (!ft_isdigit(str[i]))
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


void _test(t_cub3d *cub)
{
	printf("\n=================t_cub3d=================\n");
	//printf("screen_width : %d\n", cub->screen_width);
	//printf("screen_height : %d\n", cub->screen_height);
	//printf("map_width : %d\n", cub->map_width);
	//printf("map_height : %d\n", cub->map_height);
	printf("\n");
	printf("cam.x : %f\n", cub->cam.x);
	printf("cam.y : %f\n", cub->cam.y);
	printf("cam.dir : %c\n", cub->cam.dir);
	printf("cam.plane_x %f\n", cub->cam.plane_x);
	printf("cam.plane_y %f\n", cub->cam.plane_y);
	printf("\n");
	//printf("tex.path[0] : %s\n", cub->tex.path[0]);
	//printf("tex.path[1] : %s\n", cub->tex.path[1]);
	//printf("tex.path[2] : %s\n", cub->tex.path[2]);
	//printf("tex.path[3] : %s\n", cub->tex.path[3]);
	//printf("tex.path[4] : %s\n", cub->tex.path[4]);
	//printf("tex.rgb[0] : %x, [1] : %x\n", cub->tex.rgb[0], cub->tex.rgb[1]);
	//printf("\n");
	//printf("-------<map>-------\n");
	//for (int i = 0; i < cub->map_height; i++)
		//printf("%s\n", cub->map[i]);
	printf("=========================================\n");
}
