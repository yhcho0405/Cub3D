/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 02:56:20 by youncho           #+#    #+#             */
/*   Updated: 2021/03/20 23:10:58 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int		press_key(int key, t_cub3d *cub)
{
	cub->key[key] = true;
	return (0);
}

int		press_release(int key, t_cub3d *cub)
{
	cub->key[key] = false;
	return (0);
}

void	move_cam(t_cub3d *cub, double vx, double vy)
{
	if (cub->map[(int)cub->cam.y][(int)(cub->cam.x + vx)] != '1')
		cub->cam.x += vx;
	if (cub->map[(int)(cub->cam.y + vy)][(int)cub->cam.x] != '1')
		cub->cam.y += vy;
}

void	rotate_cam(t_camera *cam, double rot)
{
	double tmp;

	tmp = cam->dir_x;
	cam->dir_x = cam->dir_x * cos(rot) - cam->dir_y * sin(rot);
	cam->dir_y = tmp * sin(rot) + cam->dir_y * cos(rot);
	tmp = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(rot) - cam->plane_y * sin(rot);
	cam->plane_y = tmp * sin(rot) + cam->plane_y * cos(rot);
}

void	positioning_cam(t_cub3d *cub, bool *key)
{
	t_camera *cam;

	cam = &cub->cam;
	if (key[K_W])
		move_cam(cub, cam->dir_x * cam->move, cam->dir_y * cam->move);
	if (key[K_S])
		move_cam(cub, cam->dir_x * -cam->move, cam->dir_y * -cam->move);
	if (key[K_A])
		move_cam(cub, cam->dir_y * cam->move, cam->dir_x * -cam->move);
	if (key[K_D])
		move_cam(cub, cam->dir_y * -cam->move, cam->dir_x * cam->move);
	if (key[K_LEFT])
		rotate_cam(&cub->cam, -cub->cam.rotate);
	if (key[K_RIGHT])
		rotate_cam(&cub->cam, cub->cam.rotate);
	if (key[K_ESC])
		exit(0);
}
