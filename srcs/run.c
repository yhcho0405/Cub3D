/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:32:28 by youncho           #+#    #+#             */
/*   Updated: 2021/03/20 14:41:17 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_wall(t_cub3d *cub)
{
	int x;

	x = -1;
	while (++x < cub->screen_width)
	{

	}
}

int		main_loop(t_cub3d *cub)
{
	int i;
	int j;
	_test(cub);
	i = -1;
	while (++i < cub->screen_height)
	{
		j = -1;
		while (++j < cub->screen_width)
			if (i < cub->screen_height / 2)
				cub->buf[i][j] = cub->tex.rgb[CEILING];
			else
				cub->buf[i][j] = cub->tex.rgb[FLOOR];
	}
	positioning_cam(cub, cub->key);
	raycast_wall(cub);
	//raycast_spr(cub);
	return (0);
}

void	run_cub3d(t_cub3d *cub, bool is_save)
{
	preset(cub);
	if (is_save)
		return ;
	else
	{
		cub->win = mlx_new_window(cub->mlx, cub->screen_width,
									cub->screen_height, "cub3D");
		mlx_loop_hook(cub->mlx, main_loop, cub);
		mlx_hook(cub->win, X_EVENT_KEY_PRESS, 0, press_key, cub);
		mlx_hook(cub->win, X_EVENT_KEY_RELEASE, 0, press_release, cub);
		mlx_loop(cub->mlx);
	}
}
