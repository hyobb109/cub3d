/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/23 15:13:16 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	paint_map(t_vars *vars)
// {
// 	char		*str;

// 	vars->y_idx = 0;
// 	vars->hei = 0;
// 	while (vars->y_idx < vars->map_y)
// 	{
// 		str = vars->new_map[vars->y_idx];
// 		vars->x_idx = 0;
// 		vars->wid = 0;
// 		while (vars->x_idx < vars->map_x && str[vars->x_idx])
// 		{
// 			put_image_to_window(vars, str[vars->x_idx]);
// 			vars->x_idx++;
// 			if (vars->x_idx == vars->map_x)
// 				vars->hei += BLOCK_SIZE;
// 		}
// 		vars->y_idx++;
// 	}
// 	delete_images(&vars->texture);
// 	return (0);
// }

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img.addr + (y * vars->img.len + x * (vars->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	paint_minimap(int h, int w, int f_color, int c_color, t_vars *vars)
{
	if (h == 0 || h == vars->map_y * MINIMAP_SIZE - 1 || w == 0 || w == vars->map_x * MINIMAP_SIZE - 1)
		my_mlx_pixel_put(vars, w, h, 0xff0000);
	else if (vars->new_map[h / MINIMAP_SIZE][w / MINIMAP_SIZE] == -1)
		my_mlx_pixel_put(vars, w, h, c_color);
	else if (vars->new_map[h / MINIMAP_SIZE][w / MINIMAP_SIZE] == '0')
		my_mlx_pixel_put(vars, w, h, f_color);
	else if (vars->new_map[h / MINIMAP_SIZE][w / MINIMAP_SIZE] == '1')
		my_mlx_pixel_put(vars, w, h, 0xa0a0a0);
	else if (h / MINIMAP_SIZE == vars->play_y && w / MINIMAP_SIZE == vars->play_x)
		my_mlx_pixel_put(vars, w, h, 0x00ffcc);
}

int	paint_map(t_vars *vars)
{
	int	h;
	int w;
	int	f_color;
	int	c_color;

	f_color = vars->floor->r * 256 * 256 + vars->floor->g * 256 + vars->floor->b;
	c_color = vars->ceiling->r * 256 * 256 + vars->ceiling->g * 256 + vars->ceiling->b;
	// printf("color : %d %x\n", f_color, f_color);
	h = -1;
	while (++h < vars->map_y * BLOCK_SIZE)
	{
		w = -1;
		while (++w < vars->map_x * BLOCK_SIZE)
		{
			if (h < vars->map_y * MINIMAP_SIZE && w <  vars->map_x * MINIMAP_SIZE)
				paint_minimap(h, w, f_color, c_color, vars);
			else if (vars->new_map[h / BLOCK_SIZE][w / BLOCK_SIZE] == -1)
				my_mlx_pixel_put(vars, w, h, c_color);
			else if (vars->new_map[h / BLOCK_SIZE][w / BLOCK_SIZE] == '0')
				my_mlx_pixel_put(vars, w, h, f_color);
			else if (vars->new_map[h / BLOCK_SIZE][w / BLOCK_SIZE] == '1')
				my_mlx_pixel_put(vars, w, h, 0xa0a0a0);
			else if (h / BLOCK_SIZE == vars->play_y && w / BLOCK_SIZE == vars->play_x)
				my_mlx_pixel_put(vars, w, h, 0x00ffcc);
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (0);
}

// t_texture *find_image_node(t_texture **head, t_vars *vars, );




void	put_image_to_window(t_vars *vars, char map_code)
{
	if (map_code == 0)
		
	// }
	vars->wid += BLOCK_SIZE;
	// }
}

void	check_exit(t_vars *vars)
{
	if (vars->new_map[vars->play_y][vars->play_x] == 'E'
		&& vars->coll_cnt == vars->play_coll_cnt)
	{
		ft_putendl_fd("Congratuation!", 1);
		exit(1);
	}
	else if (vars->new_map[vars->play_y][vars->play_x] == 'C')
	{
		vars->new_map[vars->play_y][vars->play_x] = '0';
		paint_map(vars);
		vars->play_coll_cnt++;
	}
}

void	move_player(t_vars *vars, int keycode)
{
	vars->new_map[vars->play_y][vars->play_x] = '0';
	if (keycode == KEY_W)
		vars->play_y -= 1;
	else if (keycode == KEY_A)
		vars->play_x -= 1;
	else if (keycode == KEY_S)
		vars->play_y += 1;
	else if (keycode == KEY_D)
		vars->play_x += 1;
	vars->new_map[vars->play_y][vars->play_x] = vars->play_pos;
	mlx_clear_window(vars->mlx, vars->win);
	paint_map(vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == KEY_W && vars->play_y > 0
		&& vars->new_map[vars->play_y - 1][vars->play_x] != '1')
		move_player(vars, keycode);
	else if (keycode == KEY_A && vars->play_x > 0
		&& vars->new_map[vars->play_y][vars->play_x - 1] != '1')
		move_player(vars, keycode);
	else if (keycode == KEY_S && vars->play_y < vars->map_y
		&& vars->new_map[vars->play_y + 1][vars->play_x] != '1')
		move_player(vars, keycode);
	else if (keycode == KEY_D && vars->play_x < vars->map_x
		&& vars->new_map[vars->play_y][vars->play_x + 1] != '1')
		move_player(vars, keycode);
	ft_putnbr_fd(vars->play_mov_cnt, 1);
	write(1, "\n", 1);
	return (0);
}
