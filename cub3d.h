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
	char				*id;
	t_img				img;
	char				*file_name;
	int					*colors;
	int					img_width;
	int					img_height;
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
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}	t_player;

typedef struct s_ray
{
	int		mapX;
	int		mapY;
	double	camX;
	double	raydirX;
	double	raydirY;
	// 처음 벽 충돌까지 거리
	double	sideDistX;
	double	sideDistY;
	// 벽 충돌까지 거리 변화량
	double	deltaDistX;
	double	deltaDistY;
	// 플레이어 위치에서 카메라평면과 벽과의 수직거리 계산
	double	perpWallDist;
	// 이동방향
	int		stepX;
	int		stepY;
	// 벽 충돌 여부
	int		hit;
	// 충돌한 면
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	// 벽 텍스쳐
	int		wall_id;
	double	wallX;
	int		texX;
	int		texY;
	double	texPos;
	double	texStep;
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
	int			height;
	int			width;
	double		posX;
	double		posY;
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

// utils.c
void	measure_map_size(t_vars *vars, t_map *map, char	*str);
int		ft_exit(void);
int		count_data(t_vars *vars, char *str, int cnt);
char	*copy_str(const char *s, t_vars *vars);

// matrix.c
void	init_map(t_vars *vars, t_map *map);
void	free_matrix(char **arr);
void	free_lst(t_map *map); // todo

// image.c
void	save_element(t_vars *vars, char **texture);
void	save_color(t_vars *vars, char **tmp);

// validation.c
void	is_surrounded(t_vars *vars, char **visitied);
char	**make_visit_array(t_vars *vars);
void	validate_map(t_vars *vars);
void	check_mapfile(t_vars *vars);

// paint.c
void	paint_bg(t_vars *vars);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	paint_minimap(t_vars *vars, int width, int height);
void	init_player(t_vars *vars);
void	paint_walls(t_vars *vars, t_texture *texture, t_ray r, int x); // r -> *r 로 바꾸기
int		paint_map(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);

#endif