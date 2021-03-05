/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 06:09:30 by youncho           #+#    #+#             */
/*   Updated: 2021/03/05 21:41:37 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_resolution(t_cub3d *cub, char **info)
{
	if (!info[1] || !info[2])
		error_exit("Missing Resolution Value");
	if (!isdigit_str(info[1]))
		error_exit("Wrong Resolution Value");
	cub->screen_width = ft_atoi(info[1]) > MAX_SCREEN_WIDTH ?
						MAX_SCREEN_WIDTH : ft_atoi(info[1]);
	cub->screen_height = ft_atoi(info[2]) > MAX_SCREEN_HEIGHT ?
						MAX_SCREEN_HEIGHT : ft_atoi(info[2]);
}

void	set_color(t_cub3d *cub, char **info)
{
	char	**rgb_str;
	int		i;
	int		brightness;
	int		rgb;

	if(!(rgb_str = ft_split(info[1], ',')))
		error_exit("Allocation Fail - ft_split");
	i = -1;
	rgb = 0;
	while (++i < 3)
	{
		if (!rgb_str[i] || isdigit_str(rgb_str[i]))
			error_exit("Wrong RGB Value");
		brightness = ft_atoi(rgb_str[i]);
		if (brightness < 0 || brightness > 255)
			error_exit("Wrong RGB Range");
		rgb = (rgb << 8) | brightness;
	}
	cub->tex.rgb[info[0][0] == 'F' ? FLOOR : CEILING] = rgb;
	deallocation_2d(rgb_str);
}

int		parsing_info(t_cub3d *cub, char **info)
{
	static char *tex_name[5] = {"NO", "SO", "WE", "EA", "S"};
	int			i;
	int			fd;

	i = 0;
	while (i < 5)
		if (!ft_strncmp(info[0], tex_name[i++], 3))
		{
			if (!info[1] || !check_extension(info[1], ".xpm"))
				error_exit("Wrong texture file extension");
			if((fd = open(info[1], O_RDONLY)) == FAIL)
				error_exit("XML file open() fail");
			close(fd);
			cub->tex.path[i - 1] = ft_strdup(info[1]);
			return (INFO);
		}
	if (!ft_strncmp(info[0], "R", 2))
		set_resolution(cub, info);
	else if (!ft_strncmp(info[0], "F", 2) || !ft_strncmp(info[0], "C", 2))
		set_color(cub, info);
	else
		return (MAP);
	return (INFO);
}

void	store_map(t_cub3d *cub, t_list *cur)
{
	int		i;
	int		j;
	char	*tmp;

	i = - 1;
	while (++i < cub->map_height)
	{
		j = -1;
		tmp = (char *)cur->content;
		while (++j < ft_strlen(tmp))
		{
			if (!tmp[j] && !ft_strchr("012 NEWS\n", tmp[j]))
				error_exit("Map Element Error");
			cub->map[i][j] = tmp[j];
			if (ft_strchr("NEWS\n", tmp[j]))
			{
				if (cub->cam.dir)
					error_exit("Multiple Player Error");
				cub->cam.dir = tmp[j];
				cub->cam.x = (double)j + 0.5;
				cub->cam.y = (double)i + 0.5;
			}
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
		if (cub->map_width < (width = ft_strlen(line)))
			cub->map_width = width;
		free(line);
	}
	free(line);
	close(cub->fd);
	cub->map_height = ft_lstsize(cub->lst);
	if (!(cub->map = malloc(sizeof(char *) * (cub->map_height + 1))))
		error_exit("Allocation Fail");
	cub->map[cub->map_height] = NULL;
	store_map(cub, cub->lst);
	ft_lstclear(&(cub->lst), free);
}
