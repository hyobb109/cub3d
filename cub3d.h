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
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_IVT 2
# define EXIT_IVT 17
# define NO	1
# define SO 2
# define WE 3
# define EA 4
# define FLOOR 5
# define CEILING 6

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

typedef struct s_texture
{
	char				*id;
	void				*img;
	char				*file_name;
	int					img_width;
	int					img_height;
	struct s_texture	*prev;
	struct s_texture	*next;
}	t_texture;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}	t_color;

typedef struct s_map
{
	int		height;
	int		width;
	char	*str;
	struct s_map	*next;
}	t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	**new_map;
	char	*err_msg;
	int		fd;
	int		map_x;
	int		map_y;
	int		hei;
	int		wid;
	int		play_x; // x
	int		play_y; // x
	char	play_pos;
	int		play_mov_cnt; // x
	int		play_coll_cnt; // x
	int		coll_cnt; // x
	int		coll_x; // x
	int		coll_y; // x
	int		exit_cnt; // x 
	int		exit_x; // x
	int		exit_y; // x
	int		exit_x_back; // x
	int		exit_y_back; // x
	int		x_idx;
	int		y_idx;
	int		cur_x;
	int		cur_y;
	t_texture	*texture;
	t_color		*floor;
	t_color		*ceiling;
	t_deque	*invalid_path_deque; // x
	t_elem	*from_elem; // x
	t_elem	*to_elem; // x
	int		check_result; // 밖에서 처리
}	t_vars;

t_deque	*malloc_deque(void);
void	init_deque(t_deque *deque);
void	init_element(t_elem *element, int x, int y);
void	append_front(t_deque *deque, int x, int y);
void	append_back(t_deque *deque, int x, int y);
t_elem	*pop_front(t_deque *deque);
t_elem	*pop_back(t_deque *deque);
void	free_deque(t_deque *deque);

void	check_element(t_vars *vars);
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
void	put_image_to_window(t_texture **head, t_vars *vars, char map_code);
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

#endif