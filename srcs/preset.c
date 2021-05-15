/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:35:50 by youncho           #+#    #+#             */
/*   Updated: 2021/05/13 14:26:56 by youncho          ###   ########.fr       */
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
		_err(!(cub->tex.tile[n] = (int *)calloc(TEX_SIDE * TEX_SIDE, sizeof(int))), 1);
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
	int			i;
	int			j;
	int			max;
	t_sprite	tmp;

	i = -1;
	while (++i < cub->spr_num)
		cub->spr[i].dist = pow(cub->cam.x - cub->spr[i].x, 2.0) +
						pow(cub->cam.y - cub->spr[i].y, 2.0);
	i = -1;
	while (++i < cub->spr_num - 1)
	{
		max = i;
		j = i;
		while (++j < cub->spr_num)
			if (cub->spr[i].dist < cub->spr[j].dist)
				max = j;
		if (i != max)
		{
			tmp = cub->spr[i];
			cub->spr[i] = cub->spr[max];
			cub->spr[max] = tmp;
		}
	}
}

void	preset(t_cub3d *cub)
{
	int i;

	_err(!(cub->buf = ft_calloc(cub->screen_height, sizeof(int **))), 1);
	i = -1;
	while (++i < cub->screen_height)
		_err(!(cub->buf[i] = ft_calloc(cub->screen_width, sizeof(int *))), 1);
	_err(!(cub->z_buffer = ft_calloc(cub->screen_width, sizeof(double *))), 1);
	if (cub->cam.dir == 'N')
		rotate_cam(&cub->cam, (PI / 180) * 90);
	else if (cub->cam.dir == 'E')
		rotate_cam(&cub->cam, (PI / 180) * 0);
	else if (cub->cam.dir == 'W')
		rotate_cam(&cub->cam, (PI / 180) * 180);
	else if (cub->cam.dir == 'S')
		rotate_cam(&cub->cam, (PI / 180) * 270);
	cub->mlx = mlx_init();
	store_tex(cub, cub->tex.path, &cub->img);
	set_spr_loc(cub);
	cub->img.ptr = mlx_new_image(cub->mlx, cub->screen_width,
									cub->screen_height);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.ptr, &cub->img.bpp,
									&cub->img.line_size, &cub->img.endian);
}

void	set_spr_tex(t_cub3d *cub, t_spr_ray *sray, int x)
{
	int y;
	int draw;
	int color;
	int side_len;

	side_len = cub->img.width;
	sray->tex_x = (int)((side_len * (x - (-sray->width / 2 + sray->screen_x)) *
								side_len / sray->width) / side_len);
	if (0 < sray->transform_y && 0 < x && x < cub->screen_width &&
		sray->transform_y < cub->z_buffer[x])
	{
		y = sray->draw_start_y - 1;
		while (++y < sray->draw_end_y)
		{
			draw = (y - sray->v_move_screen) * side_len - cub->screen_height *
							(side_len / 2) + sray->height * (side_len / 2);
			sray->tex_y = ((draw * side_len) / sray->height) / side_len;
			color = cub->tex.tile[4][abs((side_len * sray->tex_y +
					(side_len - sray->tex_x - 1)) % (side_len * side_len))];
			if ((color & 0x00FFFFFF) != 0)
				cub->buf[y][x] = color;
		}
	}
}
