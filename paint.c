// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   paint.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
// /*   Updated: 2023/06/16 21:36:42 by hyobicho         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3d.h"

// int	paint_map(t_vars *vars)
// {
// 	t_texture		*head;
// 	char		*str;

// 	head = NULL;
// 	save_element(vars, tmp);
// 	vars->y_idx = 0;
// 	vars->hei = 0;
// 	while (vars->y_idx < vars->map_y)
// 	{
// 		str = vars->new_map[vars->y_idx];
// 		vars->x_idx = 0;
// 		vars->wid = 0;
// 		while (vars->x_idx < vars->map_x && str[vars->x_idx])
// 		{
// 			put_image_to_window(&head, vars, str[vars->x_idx]);
// 			vars->x_idx++;
// 			if (vars->x_idx == vars->map_x)
// 				vars->hei += BLOCK_SIZE;
// 		}
// 		vars->y_idx++;
// 	}
// 	delete_images(&head);
// 	return (0);
// }

// void	put_image_to_window(t_texture **head, t_vars *vars, char map_code)
// {
// 	t_texture	*back_img;
// 	t_texture	*stuff_img;

// 	stuff_img = 0;
// 	back_img = 0;
// 	back_img = find_image_node(head, vars, 'B');
// 	mlx_put_image_to_window(vars->mlx, vars->win,
// 		back_img->img, vars->wid, vars->hei);
// 	if (map_code != '0')
// 	{
// 		stuff_img = find_image_node(head, vars, map_code);
// 		mlx_put_image_to_window(vars->mlx, vars->win,
// 			stuff_img->img, vars->wid, vars->hei);
// 	}
// 	vars->wid += BLOCK_SIZE;
// }

// void	check_exit(t_vars *vars)
// {
// 	if (vars->new_map[vars->play_y][vars->play_x] == 'E'
// 		&& vars->coll_cnt == vars->play_coll_cnt)
// 	{
// 		ft_putendl_fd("Congratuation!", 1);
// 		exit(1);
// 	}
// 	else if (vars->new_map[vars->play_y][vars->play_x] == 'C')
// 	{
// 		vars->new_map[vars->play_y][vars->play_x] = '0';
// 		paint_map(vars);
// 		vars->play_coll_cnt++;
// 	}
// }

// void	move_player(t_vars *vars, int keycode)
// {
// 	vars->new_map[vars->play_y][vars->play_x] = '0';
// 	if (keycode == KEY_W)
// 		vars->play_y -= 1;
// 	else if (keycode == KEY_A)
// 		vars->play_x -= 1;
// 	else if (keycode == KEY_S)
// 		vars->play_y += 1;
// 	else if (keycode == KEY_D)
// 		vars->play_x += 1;
// 	vars->play_mov_cnt++;
// 	check_exit(vars);
// 	vars->new_map[vars->play_y][vars->play_x] = 'P';
// 	if (vars->coll_cnt != vars->play_coll_cnt
// 		&& (vars->play_x != vars->exit_x_back
// 			|| vars->play_y != vars->exit_y_back))
// 		vars->new_map[vars->exit_y_back][vars->exit_x_back] = 'E';
// 	mlx_clear_window(vars->mlx, vars->win);
// 	paint_map(vars);
// }

// int	key_hook(int keycode, t_vars *vars)
// {
// 	if (keycode == KEY_ESC)
// 	{
// 		mlx_destroy_window(vars->mlx, vars->win);
// 		exit(0);
// 	}
// 	else if (keycode == KEY_W && vars->play_y > 0
// 		&& vars->new_map[vars->play_y - 1][vars->play_x] != '1')
// 		move_player(vars, keycode);
// 	else if (keycode == KEY_A && vars->play_x > 0
// 		&& vars->new_map[vars->play_y][vars->play_x - 1] != '1')
// 		move_player(vars, keycode);
// 	else if (keycode == KEY_S && vars->play_y < vars->map_y
// 		&& vars->new_map[vars->play_y + 1][vars->play_x] != '1')
// 		move_player(vars, keycode);
// 	else if (keycode == KEY_D && vars->play_x < vars->map_x
// 		&& vars->new_map[vars->play_y][vars->play_x + 1] != '1')
// 		move_player(vars, keycode);
// 	ft_putnbr_fd(vars->play_mov_cnt, 1);
// 	write(1, "\n", 1);
// 	return (0);
// }
