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

# define BLOCK_SIZE 64
# define MINIMAP_SIZE 10
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
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768


typedef struct s_elem
{
	int				x;
	int				y;
	struct s_elem	*prev;
	struct s_elem	*next;
}	t_elem;

typedef struct s_deque
{
	t_elem	*head;
	t_elem	*tail;
	int		len;
}	t_deque;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}	t_img;

typedef struct s_color
{
	int				t;
	int				r;
	int				g;
	int				b;
}	t_color;

typedef struct s_texture
{
	char				*id;
	t_img				img;
	char				*file_name;
	int					*p;
	int					**colors;
	long long			trgb;
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
	char		*err_msg;
	int			fd;
	int			map_x;
	int			map_y;
	int			height;
	int			width;
	double		posX;
	double		posY;
	double		angle;
	int			play_x;
	int			play_y;
	char		play_pos;
	int			play_mov_cnt; // x
	int			play_coll_cnt; // x
	int			coll_cnt; // x
	int			coll_x; // x
	int			coll_y; // x
	int			exit_cnt; // x 
	int			exit_x; // x
	int			exit_y; // x
	int			exit_x_back; // x
	int			exit_y_back; // x
	int			x_idx;
	int			y_idx;
	int			cur_x;
	int			cur_y;
	int			floor;
	int 		ceiling;
	t_texture	texture[4];
	t_deque		*invalid_path_deque; // x
	t_elem		*from_elem; // x
	t_elem		*to_elem; // x
	int			check_result; // 밖에서 처리
}	t_vars;

t_deque	*malloc_deque(void);
void	init_deque(t_deque *deque);
void	init_element(t_elem *element, int x, int y);
void	append_front(t_deque *deque, int x, int y);
void	append_back(t_deque *deque, int x, int y);
t_elem	*pop_front(t_deque *deque);
t_elem	*pop_back(t_deque *deque);
void	free_deque(t_deque *deque);
void	init_player(t_vars *vars);
void	check_mapfile(t_vars *vars);
void	init_vars(t_vars *vars, char *map_name);
void	measure_map_size(t_vars *vars);
void	init_map(t_vars *vars, t_map *map);
char	**free_matrix(char **arr);
void	count_stuff(t_vars *vars, char *str, int y_idx);
void	init_coll_info(t_vars *vars, int x_idx, int y_idx);
void	init_exit_info(t_vars *vars, int x_idx, int y_idx);
void	init_player_info(t_vars *vars, int x_idx, int y_idx);
void	validate_map(t_vars *vars);
void	is_surrounded(t_vars *vars, char **visited);
int		validate_path(t_vars *vars); 
char	**make_visit_array(t_vars *vars);
int		is_continued(t_vars *vars);
int		is_stuff(t_vars *vars);
int		bfs_detail(t_vars *vars, t_elem *cur_elem, t_deque *check_queue, \
					char **check_array);
int		paint_map(t_vars *vars);
void	put_image_to_window(t_vars *vars, char map_code);
void	move_player(t_vars *vars, int keycode);
int		key_hook(int keycode, t_vars *vars);
int		ft_exit(void);
void	check_exit(t_vars *vars);
void	save_element(t_vars *vars, char **texture);
t_texture	*texture_lstadd_back(t_vars *vars, char **texture);
void		get_texture_file_name(t_texture *new_node, char **texture);
t_texture	*init_texture_node(t_texture *new_node, t_vars *vars, char **texture);
void	delete_images(t_texture **head);
void	print_textures(t_texture *head);
void print_strs(char **strs);
void	paint_walls(t_vars *vars, t_texture *texture, t_ray r, int x);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

#endif