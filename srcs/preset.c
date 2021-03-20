/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:35:50 by youncho           #+#    #+#             */
/*   Updated: 2021/03/20 11:20:27 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_tex(t_cub3d *cub, char **path, t_image *img)
{
	int		n;
	int		i;
	int		j;

	n = -1;
	while (++n < 5)
	{
		img->ptr = mlx_xpm_file_to_image(cub->mlx, path[n], &img->width,
									&img->height);
		img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
									&img->line_size, &img->endian);
		i = -1;
		while (++i < img->height)
		{
			j = -1;
			while (++j < img->width)
				cub->tex.tile[n][img->width * i + j] =
				img->data[img->width * i + (img->width - j - 1)];
		}
		mlx_destroy_image(cub->mlx, img->ptr);
		free(path[n]);
	}
}

void	set_spr_loc(t_cub3d *cub)
{
	int i;
	int j;
	int n;

	_err(!(cub->spr = malloc(sizeof(t_sprite) * cub->spr_num)), 1);
	n = 0;
	i = -1;
	while (++i < cub->map_height && (j = -1))
		while (++j < cub->map_width)
			if (cub->map[i][j] == '2')
			{
				cub->spr[n].x = (double)j + 0.5;
				cub->spr[n++].y = (double)i + 0.5;
			}
}

void	sort_spr(t_cub3d *cub)
{
	int i;

	i = -1;
	while (++i < cub->spr_num)
		cub->spr[i].dist = pow(cub->cam.x - cub->spr[i].x, 2.0) +
						pow(cub->cam.y - cub->spr[i].y, 2.0);
}

void	allocate_buffer(t_cub3d *cub)
{
	int i;

	_err(!(cub->buf = ft_calloc(cub->screen_height, sizeof(int **))), 1);
	i = -1;
	while (++i < cub->screen_height)
		_err(!(cub->buf[i] = ft_calloc(cub->screen_width, sizeof(int *))), 1);
	_err(!(cub->z_buffer = ft_calloc(cub->screen_width, sizeof(double *))), 1);
}

void	preset(t_cub3d *cub)
{
	allocate_buffer(cub);
	if (cub->cam.dir == 'N')
		rotate_cam(&cub->cam, (PI / 180) * 90);
	else if (cub->cam.dir == 'E')
		rotate_cam(&cub->cam, (PI / 180) * 0);
	else if (cub->cam.dir == 'W')
		rotate_cam(&cub->cam, (PI / 180) * 180);
	else if (cub->cam.dir == 'S')
		rotate_cam(&cub->cam, (PI / 180) * 270);
	cub->mlx = mlx_init();
	store_tex(cub, &cub->tex.path, &cub->img);
	set_spr_loc(cub);
	cub->img.ptr = mlx_new_image(cub->mlx, cub->screen_width,
									cub->screen_height);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.ptr, &cub->img.bpp,
									&cub->img.line_size, &cub->img.endian);
}
