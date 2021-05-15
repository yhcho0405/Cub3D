/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 12:17:38 by youncho           #+#    #+#             */
/*   Updated: 2021/05/15 12:30:58 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	screenshot(t_cub3d *cub)
{
	int fd;
	int size;

	raycast_wall(cub);
	raycast_spr(cub, &cub->cam, &cub->sray);
	size = 54 + 3 * cub->screen_width * cub->map_height;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00755);
	if (fd < 0)
		error_exit("open() fail");
}
