/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:25:16 by youncho           #+#    #+#             */
/*   Updated: 2021/03/05 21:11:35 by youncho          ###   ########.fr       */
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
}

int		main_arg_handler(int argc, char **argv, t_cub3d *cub)
{
	int		is_save;

	if (argc == 2)
		is_save = FALSE;
	else if (argc == 3 && !ft_strncmp(argv[2], "--save", 7))
		is_save = TRUE;
	else
		error_exit("Wrong Arguments");
	if (!check_extension(argv[1], ".cub"))
		error_exit("Wrong map file extension");
	if((cub->fd = open(argv[1], O_RDONLY)) == FAIL)
		error_exit("CUB file open() fail");
	return (is_save);
}

void	parse_handler(t_cub3d *cub)
{
	char	*line;
	char	**split;
	int		field;
	int		i;

	field = INFO;
	while (get_next_line(cub->fd, &line) > 0)
	{
		if (field == INFO && !line[0])
			continue ;
		if (field == INFO)
		{
			if(!(split = ft_split(line, ' ')))
				error_exit("Allocation Fail - ft_split");
			field = parsing_info(cub, split);
			deallocation_2d(split);
		}
		if (field == MAP)
		{
			parsing_map(cub, line);
			break ;
		}
		free(line);
	}
}

int		main(int argc, char **argv)
{
	int		is_save;
	t_cub3d	cub;

	is_save =
	main_arg_handler(argc, argv, &cub);
	init_cub3d(&cub);
	parse_handler(&cub);
	//run_cub3d(&cub, is_save);
	return (0);
}
