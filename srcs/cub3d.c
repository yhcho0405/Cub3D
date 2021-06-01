/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:25:16 by youncho           #+#    #+#             */
/*   Updated: 2021/06/01 16:16:45 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub3d(t_cub3d *cub)
{
	cub->screen_width = 0;
	cub->screen_height = 0;
	cub->map_width = 0;
	cub->map_height = 0;
	cub->cam.dir = 0;
	cub->cam.x = 0;
	cub->cam.y = 0;
	cub->cam.dir_x = 1.0;
	cub->cam.dir_y = 0.0;
	cub->cam.plane_x = 0.0;
	cub->cam.plane_y = 0.66;
	cub->cam.move = 0.07;
	cub->cam.rotate = 0.06;
	cub->tex.rgb[0] = -1;
	cub->tex.rgb[1] = -1;
	cub->spr_num = 0;
	cub->parse_chk = 0;
	ft_memset(cub->key, 0, sizeof(cub->key));
}

int		main_arg_handler(int argc, char **argv, t_cub3d *cub)
{
	bool	is_save;

	is_save = false;
	if (argc == 2)
		is_save = false;
	else if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		is_save = true;
	else
		error_exit("Wrong Arguments");
	if (!check_extension(argv[1], ".cub"))
		error_exit("Wrong map file extension");
	cub->fd = open(argv[1], O_RDONLY);
	if (cub->fd == FAIL)
		error_exit("CUB file open() fail");
	return (is_save);
}

void	parse_handler(t_cub3d *cub)
{
	char	*line;
	char	**split;
	int		cnt;

	cnt = 0;
	while (get_next_line(cub->fd, &line) > 0)
	{
		if (line[0])
		{
			if (cnt < 8 && ++cnt)
			{
				error_handler(!(split = ft_split(line, ' ')), 1);
				parsing_info(cub, split, 0);
				deallocation_2d(split);
				error_handler((cnt == 8) && (cub->parse_chk != 0b11111111), 4);
			}
			else if ((cnt == 8) && (cub->parse_chk == 0b11111111))
			{
				parsing_map(cub, line);
				break ;
			}
		}
		free(line);
	}
}

int		close_all(t_cub3d *cub, int win)
{
	int	i;

	i = -1;
	deallocation_2d(cub->map);
	while (++i < cub->screen_height)
		free(cub->buf[i]);
	free(cub->buf);
	free(cub->z_buffer);
	i = -1;
	while (++i < 5)
		free(cub->tex.tile[i]);
	free(cub->spr);
	if (win == 1)
		mlx_destroy_window(cub->mlx, cub->win);
	free(cub->mlx);
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	bool	is_save;
	t_cub3d	cub;

	is_save = main_arg_handler(argc, argv, &cub);
	init_cub3d(&cub);
	parse_handler(&cub);
	run_cub3d(&cub, is_save);
	return (0);
}
