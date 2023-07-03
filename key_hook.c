/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:36:08 by hyobicho          #+#    #+#             */
/*   Updated: 2023/07/03 20:30:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	adjust_pos_range(t_vars *vars)
{
	if (vars->new_map[(int)(vars->pos_y + 0.01)][(int)vars->pos_x] == '1')
		vars->pos_y -= 0.01;
	else if (vars->new_map[(int)(vars->pos_y - 0.01)][(int)vars->pos_x] == '1')
		vars->pos_y += 0.01;
	else if (vars->new_map[(int)vars->pos_y][(int)(vars->pos_x + 0.01)] == '1')
		vars->pos_x -= 0.01;
	else if (vars->new_map[(int)vars->pos_y][(int)(vars->pos_x - 0.01)] == '1')
		vars->pos_x += 0.01;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_up(vars);
	else if (keycode == KEY_S)
		move_down(vars);
	else if (keycode == KEY_D)
		move_left(vars);
	else if (keycode == KEY_A)
		move_right(vars);
	else if (keycode == KEY_LEFT)
		rotate_left(vars);
	else if (keycode == KEY_RIGHT)
		rotate_right(vars);
	adjust_pos_range(vars);
	return (0);
}
