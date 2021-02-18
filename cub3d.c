/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:25:16 by youncho           #+#    #+#             */
/*   Updated: 2021/02/19 06:34:37 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub3d(t_cub3d *cub)
{
	cub->screen_width = 0;
	cub->screen_height = 0;
	cub->map_width = 0;
	cub->map_height = 0;
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
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		error_exit("Wrong map file extension");
	if((cub->fd = open(argv[1], O_RDONLY)) == FAIL)
		error_exit("file open fail");
	return (is_save);
}

int		main(int argc, char **argv)
{
	int		is_save;
	t_cub3d	cub;

	is_save =
	main_arg_handler(argc, argv, &cub);
	init_cub3d(&cub);
	parsing_map(&cub);
	run_cub3d(&cub, is_save);
	return (0);
}
