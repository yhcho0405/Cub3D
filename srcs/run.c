/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:32:28 by youncho           #+#    #+#             */
/*   Updated: 2021/05/17 12:01:28 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rendering(t_cub3d *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cub->screen_height)
	{
		j = -1;
		while (++j < cub->screen_width)
			cub->img.data[cub->screen_width * i + j] = cub->buf[i][j];
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.ptr, 0, 0);
}

void	raycast_wall(t_cub3d *cub)
{
	int			x;
	t_camera	*cam;
	t_raycast	*ray;

	x = -1;
	cam = &cub->cam;
	ray = &cub->ray;
	while (++x < cub->screen_width)
	{
		ray->cam_x = (2 * x / (double)cub->screen_width) - 1;
		ray->dir_x = cam->dir_x + cam->plane_x * ray->cam_x;
		ray->dir_y = cam->dir_y + cam->plane_y * ray->cam_x;
		ray->map_x = (int)cam->x;
		ray->map_y = (int)cam->y;
		ray->delta_dist_x = fabs(1 / ray->dir_x);
		ray->delta_dist_y = fabs(1 / ray->dir_y);
		ray->hit = 0;
		pre_dda(cam, ray);
		calc_dda(cub, ray);
		set_wall_dist_height(cub, ray);
		set_wall_tex(cub, cam, ray, x);
		cub->z_buffer[x] = cub->ray.perp_wall_dist;
	}
}

void	raycast_spr(t_cub3d *cub, t_camera *cam, t_spr_ray *sray)
{
	int	i;
	int	x;

	sort_spr(cub);
	i = -1;
	while (++i < cub->spr_num)
	{
		sray->x = cam->x - cub->spr[i].x;
		sray->y = cam->y - cub->spr[i].y;
		sray->inversion_detection = 1.0
			/ (cam->plane_x * -cam->dir_y - -cam->dir_x * cam->plane_y);
		sray->transform_x = sray->inversion_detection
			* (-cam->dir_y * sray->x - -cam->dir_x * sray->y);
		sray->transform_y = sray->inversion_detection
			* (-cam->plane_y * sray->x + cam->plane_x * sray->y);
		sray->screen_x = (int)((cub->screen_width / 2)
				* (1 - sray->transform_x / sray->transform_y));
		sray->v_move_screen = (int)(V_MODE / sray->transform_y);
		calc_spr(cub, &cub->sray);
		x = cub->sray.draw_start_x - 1;
		while (++x < cub->sray.draw_end_x)
			set_spr_tex(cub, &cub->sray, x);
	}
}

int	main_loop(t_cub3d *cub)
{
	int	i;

	i = -1;
	positioning_cam(cub, cub->key);
	raycast_wall(cub);
	raycast_spr(cub, &cub->cam, &cub->sray);
	rendering(cub);
	return (0);
}

void	run_cub3d(t_cub3d *cub, bool is_save)
{
	preset(cub);
	if (is_save)
		save(cub);
	else
	{
		cub->win = mlx_new_window(cub->mlx, cub->screen_width,
				cub->screen_height, "cub3D");
		mlx_hook(cub->win, X_EVENT_KEY_PRESS, 0, press_key, cub);
		mlx_hook(cub->win, X_EVENT_KEY_RELEASE, 0, release_key, cub);
		mlx_loop_hook(cub->mlx, main_loop, cub);
		mlx_loop(cub->mlx);
	}
}
