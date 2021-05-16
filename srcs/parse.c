/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 06:09:30 by youncho           #+#    #+#             */
/*   Updated: 2021/05/16 11:09:02 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_resolution(t_cub3d *cub, char **info)
{
	if (!info[1] || !info[2])
		error_exit("Missing Resolution Value");
	if (!isdigit_str(info[1]) || !isdigit_str(info[2]))
		error_exit("Wrong Resolution Value");
	cub->screen_width = ft_atoi(info[1]);
	if (ft_atoi(info[1]) > MAX_SCREEN_WIDTH)
		cub->screen_width = MAX_SCREEN_WIDTH;
	else if (ft_atoi(info[1]) < MIN_SCREEN_WIDTH)
		cub->screen_width = MIN_SCREEN_WIDTH;
	cub->screen_height = ft_atoi(info[2]);
	if (ft_atoi(info[2]) > MAX_SCREEN_HEIGHT)
		cub->screen_height = MAX_SCREEN_HEIGHT;
	else if (ft_atoi(info[2]) < MIN_SCREEN_HEIGHT)
		cub->screen_height = MIN_SCREEN_HEIGHT;
}

void	set_color(t_cub3d *cub, char **info)
{
	char	**rgb_str;
	int		i;
	int		brightness;
	int		rgb;

	_err(!(rgb_str = ft_split(info[1], ',')), 1);
	i = -1;
	rgb = 0;
	while (++i < 3)
	{
		if (!rgb_str[i] || !isdigit_str(rgb_str[i]))
			error_exit("Wrong RGB Value");
		brightness = ft_atoi(rgb_str[i]);
		if (brightness < 0 || brightness > 255)
			error_exit("Wrong RGB Range");
		rgb = (rgb << 8) | brightness;
	}
	if (info[0][0] == 'F')
		cub->tex.rgb[FLOOR] = rgb;
	else if (info[0][0] == 'C')
		cub->tex.rgb[CEILING] = rgb;
	deallocation_2d(rgb_str);
}

int	parsing_info(t_cub3d *cub, char **info, int i)
{
	const char	*tex_name[5] = {"NO", "SO", "WE", "EA", "S"};
	int			fd;

	while (i < 5)
	{
		if (!ft_strncmp(info[0], tex_name[i++], 3))
		{
			if (!info[1] || !check_extension(info[1], ".xpm"))
				error_exit("Wrong texture file extension");
			fd = open(info[1], O_RDONLY);
			if (fd == FAIL)
				error_exit("XPM file open() fail");
			close(fd);
			cub->tex.path[i - 1] = ft_strdup(info[1]);
			return (INFO);
		}
	}
	if (!ft_strncmp(info[0], "R", 2))
		set_resolution(cub, info);
	else if (!ft_strncmp(info[0], "F", 2) || !ft_strncmp(info[0], "C", 2))
		set_color(cub, info);
	else
		return (MAP);
	return (INFO);
}

void	store_map(t_cub3d *cub, t_list *cur, int i, int j)
{
	char	*tmp;

	while (++i < cub->map_height)
	{
		tmp = (char *)cur->content;
		_err(!(cub->map[i] = malloc(cub->map_width + 1)), (j = -1) + 2);
		while (++j < cub->map_width)
			cub->map[i][j] = ' ';
		cub->map[i][cub->map_width] = (j = -1) + 1;
		while (++j < (int)ft_strlen(tmp))
		{
			_err(!tmp[j] && !ft_strchr("012 NEWS\n", tmp[j]), 2);
			cub->map[i][j] = tmp[j];
			if (ft_strchr("NEWS", tmp[j]))
			{
				_err(cub->cam.dir, 3);
				cub->cam.dir = tmp[j];
				cub->cam.x = (double)j + 0.5;
				cub->cam.y = (double)i + 0.5;
			}
			else if (tmp[j] == '2')
				cub->spr_num++;
		}
		cur = cur->next;
	}
}

void	parsing_map(t_cub3d *cub, char *line)
{
	int	width;

	cub->lst = ft_lstnew(ft_strdup(line));
	cub->map_width = ft_strlen(line);
	free(line);
	while (get_next_line(cub->fd, &line) > 0)
	{
		if (!line[0])
			break ;
		ft_lstadd_back(&cub->lst, ft_lstnew(ft_strdup(line)));
		width = ft_strlen(line);
		if (cub->map_width < width)
			cub->map_width = width;
		free(line);
	}
	free(line);
	close(cub->fd);
	cub->map_height = ft_lstsize(cub->lst);
	_err(!(cub->map = malloc(sizeof(char *) * (cub->map_height + 1))), 1);
	cub->map[cub->map_height] = NULL;
	store_map(cub, cub->lst, -1, -1);
	ft_lstclear(&(cub->lst), free);
	check_valid(cub);
}
