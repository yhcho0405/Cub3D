/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youncho <youncho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 21:25:13 by youncho           #+#    #+#             */
/*   Updated: 2021/05/16 11:29:00 by youncho          ###   ########.fr       */
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

# define TEX_SIDE 256

# define TRUE 1
# define FALSE 0
# define FAIL -1

# define INFO 1
# define MAP 2

# define FLOOR 0
# define CEILING 1

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

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

# define V_MODE 0.0

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define PI 3.1415926535897

typedef struct s_texture
{
	char		*path[6];
	int			*tile[6];
	int			rgb[2];
}				t_texture;

typedef struct s_camera
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

typedef struct s_image
{
	int			width;
	int			height;
	void		*ptr;
	int			*data;
	int			line_size;
	int			bpp;
	int			endian;
}				t_image;

typedef struct s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef struct s_raycast
{
	double		cam_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			tex_x;
	int			tex_y;
}				t_raycast;

typedef struct s_spr_ray
{
	double		x;
	double		y;
	double		inversion_detection;
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			v_move_screen;
	int			height;
	int			width;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
	int			tex_x;
	int			tex_y;
}				t_spr_ray;

typedef struct s_cub3d
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
	t_raycast	ray;
	t_spr_ray	sray;
}				t_cub3d;

//	cub3d.c
void	init_cub3d(t_cub3d *cub);
int		main_arg_handler(int argc, char **argv, t_cub3d *cub);
void	parse_handler(t_cub3d *cub);

//	parse.c
void	set_resolution(t_cub3d *cub, char **info);
void	set_color(t_cub3d *cub, char **info);
int		parsing_info(t_cub3d *cub, char **info, int i);
void	store_map(t_cub3d *cub, t_list *cur, int i, int j);
void	parsing_map(t_cub3d *cub, char *line);

//	preset.c
void	store_tex(t_cub3d *cub, char **path, t_image *img);
void	set_spr_loc(t_cub3d *cub);
void	sort_spr(t_cub3d *cub);
void	preset(t_cub3d *cub);
void	set_spr_tex(t_cub3d *cub, t_spr_ray *sray, int x);

//	run.c
void	rendering(t_cub3d *cub);
void	raycast_wall(t_cub3d *cub);
void	raycast_spr(t_cub3d *cub, t_camera *cam, t_spr_ray *sray);
int		main_loop(t_cub3d *cub);
void	run_cub3d(t_cub3d *cub, bool is_save);

// move.c
int		press_key(int key, t_cub3d *cub);
int		release_key(int key, t_cub3d *cub);
void	move_cam(t_cub3d *cub, double vx, double vy);
void	rotate_cam(t_camera *cam, double rot);
void	positioning_cam(t_cub3d *cub, bool *key);

//	racast.c
void	pre_dda(t_camera *cam, t_raycast *ray);
void	calc_dda(t_cub3d *cub, t_raycast *ray);
void	set_wall_dist_height(t_cub3d *cub, t_camera *cam, t_raycast *ray);
void	set_wall_tex(t_cub3d *cub, t_camera *cam, t_raycast *ray, int x);
void	calc_spr(t_cub3d *cub, t_spr_ray *sray);

//	check.c
void	map_check_row(t_cub3d *cub);
void	map_check_col(t_cub3d *cub);
void	check_valid(t_cub3d *cub);
int		check_extension(char *s, char *ex);
int		isdigit_str(char *str);

//	utils.c
void	error_exit(char *str);
void	_err(bool err, int code);
void	deallocation_2d(char **arr);
void	make_bmp(t_cub3d *cub, int fd);
void	save(t_cub3d *cub);

#endif
