/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:25:13 by youncho           #+#    #+#             */
/*   Updated: 2021/02/19 05:43:37 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>

# define TITLE "cub3D"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

# define TRUE 1
# define FALSE 0
# define FAIL -1

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define LEFT 123
# define DOWN 125
# define RIGHT 124

typedef struct	s_cub3d
{
	int			fd;
	int			screen_width;
	int			screen_height;
	char		**map;
	int			map_width;
	int			map_height;
	void		*mlx;
	void		*win;
}				t_cub3d;

//	utils.c
void			error_exit(char *str);

#endif
