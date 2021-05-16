/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 03:25:42 by youncho           #+#    #+#             */
/*   Updated: 2021/05/16 09:08:24 by youncho          ###   ########.fr       */
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
}

int	isdigit_str(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	deallocation_2d(char **arr)
{
	size_t	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/*
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
*/
