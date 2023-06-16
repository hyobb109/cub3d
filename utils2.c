/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:53:36 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 16:20:14 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_stuff(t_vars *vars, char *str, int y_idx)
{
	int	x_idx;

	x_idx = 0;
	while (x_idx < vars->map_x && str[x_idx])
	{
		if (str[x_idx] == 'C')
			init_coll_info(vars, x_idx, y_idx);
		else if (str[x_idx] == 'E')
			init_exit_info(vars, x_idx, y_idx);
		else if (str[x_idx] == 'P')
			init_player_info(vars, x_idx, y_idx);
		x_idx++;
	}
}

void	init_coll_info(t_vars *vars, int x_idx, int y_idx)
{
	vars->coll_x = x_idx;
	vars->coll_y = y_idx;
	vars->coll_cnt += 1;
	append_back(vars->invalid_path_deque, vars->coll_x, vars->coll_y);
}

void	init_exit_info(t_vars *vars, int x_idx, int y_idx)
{
	vars->exit_x = x_idx;
	vars->exit_y = y_idx;
	vars->exit_x_back = x_idx;
	vars->exit_y_back = y_idx;
	vars->exit_cnt += 1;
	append_back(vars->invalid_path_deque, vars->exit_x, vars->exit_y);
}

void	init_player_info(t_vars *vars, int x_idx, int y_idx)
{
	vars->play_x = x_idx;
	vars->play_y = y_idx;
	vars->play_str_cnt += 1;
	append_front(vars->invalid_path_deque, vars->play_x, vars->play_y);
}
