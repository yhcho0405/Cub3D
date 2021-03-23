/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:48:31 by youncho           #+#    #+#             */
/*   Updated: 2021/03/24 04:35:02 by youncho          ###   ########.fr       */
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

	if (ray->side == EAST || ray->side == WEST)
		ray->wall_x = cam->y + ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = cam->x + ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)cub->img.width);
	if (ray->side == EAST || ray->side == SOUTH)
		ray->tex_x = cub->img.width - ray->tex_x - 1;
	ray->step = 1.0 * cub->img.height / ray->line_height;
	ray->tex_pos = (ray->draw_start - cub->screen_height / 2
						+ ray->line_height / 2) * ray->step;
	y = -1;
	while (++y < cub->screen_height)
		if (ray->draw_start <= y && y < ray->draw_end)
		{
			ray->tex_y = (int)ray->tex_pos & (cub->img.height - 1);
			ray->tex_pos += ray->step;
			cub->buf[y][x] = cub->tex.tile[ray->side][cub->img.height
											 * ray->tex_y + ray->tex_x];
		}
		else
			cub->buf[y][x] = cub->tex.rgb[(int)(y < cub->screen_height / 2)];
}

void	calc_spr(t_cub3d *cub, t_spr_ray *sray)
{
	int div;

	div = 1;
	sray->height = (int)fabs((cub->screen_height / sray->transform_y) / div);
	sray->draw_start_y =
		-sray->height / 2 + cub->screen_height / 2 + sray->v_move_screen;
	if (sray->draw_start_y < 0)
		sray->draw_start_y = 0;
	sray->draw_end_y =
		sray->height / 2 + cub->screen_height / 2 + sray->v_move_screen;
	if (sray->draw_end_y >= cub->screen_height)
		sray->draw_end_y = cub->screen_height - 1;
	div = 1;
	sray->width = (int)fabs((cub->screen_height / sray->transform_y) / div);
	sray->draw_start_x = -sray->width / 2 + sray->screen_x;
	if (sray->draw_start_x < 0)
		sray->draw_start_x = 0;
	sray->draw_end_x = sray->width / 2 + sray->screen_x;
	if (sray->draw_end_x >= cub->screen_width)
		sray->draw_end_x = cub->screen_width - 1;
}
