/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 16:43:38 by hyobicho          #+#    #+#             */
/*   Updated: 2023/07/03 20:30:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

# define X_SIDE 0
# define Y_SIDE 1
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_EVT 2
# define EXIT_EVT 17
# define NO	0
# define SO 1
# define WE 2
# define EA 3
# define PI 3.141592
# define SPEED 0.2
# define MINIMAP_SIZE 10
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	img;
	char	*file_name;
	int		*colors;
	int		img_width;
	int		img_height;
}	t_texture;

typedef struct s_map
{
	int				height;
	int				width;
	char			*str;
	struct s_map	*next;
}	t_map;

typedef struct s_player
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	int		cur_x;
	int		cur_y;
	double	cam_x;
	double	raydir_x;
	double	raydir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		wall_id;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	tex_step;
}	t_ray;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	p;
	char		**new_map;
	int			fd;
	int			map_x;
	int			map_y;
	double		pos_x;
	double		pos_y;
	double		angle;
	char		play_pos;
	int			floor;
	int			ceiling;
	t_texture	texture[4];
}	t_vars;

// init.c
void	init_vars(t_vars *vars, char *map_name);
t_map	*init_map_node(char *str, int h, t_vars *vars);
char	*init_map_head(t_vars *vars, t_map **map);

// key_hook.c
int		key_hook(int keycode, t_vars *vars);

// key_move.c
void	move_up(t_vars *vars);
void	move_down(t_vars *vars);
void	move_left(t_vars *vars);
void	move_right(t_vars *vars);

// key_rotate.c
void	rotate_left(t_vars *vars);
void	rotate_right(t_vars *vars);

// minimap.c
void	paint_minimap(t_vars *vars, int width, int height);

// utils.c
void	measure_map_size(t_vars *vars, t_map *map, char	*str);
int		ft_exit(void);
int		count_data(t_vars *vars, char *str, int cnt);
char	*copy_str(const char *s, t_vars *vars);

// matrix.c
void	init_map(t_vars *vars, t_map *map);
void	free_matrix(char **arr);
void	free_lst(t_map *map);

// image.c
void	save_element(t_vars *vars, char **texture);
void	save_color(t_vars *vars, char **tmp);

// validation.c
void	check_mapfile(t_vars *vars);

// paint.c
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	paint_bg(t_vars *vars);
void	paint_walls(t_vars *vars, t_texture *texture, t_ray *r, int x);

//raycasting1.c
void	init_player(t_vars *vars);
void	init_raycasting_vars1(t_vars *vars, t_ray *r, int x);
void	init_raycasting_vars2(t_vars *vars, t_ray *r);
void	raycasting(t_vars *vars, t_ray *r);

// raycasting2.c
void	init_draw_xpoints(t_vars *vars, t_ray *r);
void	init_draw_ypoints(t_ray *r);
int		paint_map(t_vars *vars);

#endif