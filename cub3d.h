/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:25:13 by youncho           #+#    #+#             */
/*   Updated: 2021/03/05 21:08:47 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define TITLE "cub3D"

# define TRUE 1
# define FALSE 0
# define FAIL -1

# define INFO 1
# define MAP 2

# define FLOOR 0
# define CEILING 1

# define MAX_SCREEN_WIDTH 1920
# define MAX_SCREEN_HEIGHT 1080
# define MIN_SCREEN_WIDTH 192
# define MIN_SCREEN_HEIGHT 108

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define LEFT 123
# define DOWN 125
# define RIGHT 124

# define TEX_SIDE 256

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17



typedef struct	s_tex
{
	char		*path[6];
	int			tile[6][TEX_SIDE * TEX_SIDE];
	int			rgb[2];
}				t_tex;

typedef struct	s_camera
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move;
	double		rotate;
	char		dir;
}				t_camera;

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
	t_camera	cam;
	t_tex		tex;
	t_list		*lst;
}				t_cub3d;


//	cub3d.c


//	parse.c
int				parsing_info(t_cub3d *cub, char **info);
void			parsing_map(t_cub3d *cub, char *line);

//	utils.c
void			error_exit(char *str);
int				check_extension(char *s, char *ex);
int				isdigit_str(char *str);
void			deallocation_2d(char **arr);




#endif
