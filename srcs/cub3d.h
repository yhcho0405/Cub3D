/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:25:13 by youncho           #+#    #+#             */
/*   Updated: 2021/03/20 11:11:10 by youncho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

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

# define K_ESC 53
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_T 2
# define K_UP 126
# define K_LEFT 123
# define K_DOWN 125
# define K_RIGHT 124
# define K_SPACE 49

# define TEX_SIDE 256

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define PI 3.1415926535897

typedef struct	s_texture
{
	char		*path[6];
	int			tile[6][TEX_SIDE * TEX_SIDE];
	int			rgb[2];
}				t_texture;

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

typedef struct	s_image
{
	int			width;
	int			height;
	void		*ptr;
	int			*data;
	int			line_size;
	int			bpp;
	int			endian;
}				t_image;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef struct	s_raycast
{

}				t_raycase;

typedef struct	s_cub3d
{
	int			fd;
	int			screen_width;
	int			screen_height;
	int			**buf;
	char		**map;
	int			map_width;
	int			map_height;
	void		*mlx;
	void		*win;
	int			spr_num;
	bool		key[128];
	double		*z_buffer;
	t_camera	cam;
	t_texture	tex;
	t_list		*lst;
	t_image		img;
	t_sprite	*spr;
}				t_cub3d;


//	cub3d.c


//	parse.c
int				parsing_info(t_cub3d *cub, char **info);
void			parsing_map(t_cub3d *cub, char *line);


// check.c
void			check_valid(t_cub3d *cub);


//	utils.c
void			error_exit(char *str);
int				check_extension(char *s, char *ex);
int				isdigit_str(char *str);
void			deallocation_2d(char **arr);
void			_err(bool err, int code);

void			run_cub3d(t_cub3d *cub, bool is_save);
void			preset(t_cub3d *cub);

//move.c
int				press_key(int key, t_cub3d *cub);
int				press_release(int key, t_cub3d *cub);
void			positioning_cam(t_cub3d *cub, bool *key);
void			rotate_cam(t_camera *cam, double rot);
void _test(t_cub3d *cub);


#endif
