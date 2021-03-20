/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:48:31 by youncho           #+#    #+#             */
/*   Updated: 2021/03/20 23:14:29 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pre_dda(t_camera *cam, t_raycast *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cam->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cam->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cam->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cam->y) * ray->delta_dist_y;
	}
}

void	calc_dda(t_cub3d *cub, t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = EAST;
			if (ray->step_x == -1)
				ray->side = WEST;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = NORTH;
			if (ray->step_y == -1)
				ray->side = SOUTH;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	set_wall_dist_height(t_cub3d *cub, t_camera *cam, t_raycast *ray)
{
	if (ray->side == WEST || ray->side == EAST)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(cub->screen_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + cub->screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + cub->screen_height / 2;
	if (ray->draw_end >= cub->screen_height)
		ray->draw_end = cub->screen_height - 1;
}

void	set_wall_tex(t_cub3d *cub, t_camera *cam, t_raycast *ray, int x)
{
	int y;
	int color;

	if (ray->side == EAST || ray->side == WEST)
		ray->wall_x = cam->y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = cam->x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEX_SIDE);
	if (ray->side == EAST || ray->side == SOUTH)
		ray->tex_x = TEX_SIDE - ray->tex_x - 1;
	ray->step = 1.0 * TEX_SIDE / ray->line_height;
	ray->tex_pos = (ray->draw_start - cub->screen_height / 2
						+ ray->line_height / 2) * ray->step;
	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (TEX_SIDE - 1);
		ray->tex_pos += ray->step;
		color = cub->tex.tile[ray->side][TEX_SIDE * ray->tex_y + ray->tex_x];
		cub->buf[y][x] = color;
	}
}

void	init_raycast(t_cub3d *cub, t_camera *cam, t_raycast *ray, int x)
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
	set_wall_dist_height(cub, cam, ray);
	set_wall_tex(cub, cam, ray, x);
}
