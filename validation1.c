/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:13:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 16:20:19 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map(t_vars *vars)
{
	if (!is_rectangle(vars) || !is_surrounded(vars)
		|| !is_correct_count(vars) || !is_invalid_path(vars))
		print_error_exit(vars->err_msg);
}

int	is_rectangle(t_vars *vars)
{
	int		str_len;
	int		y_idx;

	str_len = 0;
	y_idx = 0;
	while (y_idx < vars->map_y && vars->new_map[y_idx])
	{
		str_len = ft_strlen(vars->new_map[y_idx]);
		if (vars->map_x != str_len)
		{
			vars->err_msg = "Invalid map dimension";
			return (0);
		}
		y_idx++;
	}
	return (1);
}

int	is_surrounded(t_vars *vars)
{
	char	*str;

	vars->y_idx = 0;
	while (vars->y_idx < vars->map_y)
	{
		vars->x_idx = 0;
		str = vars->new_map[vars->y_idx];
		while (vars->x_idx < vars->map_x)
		{
			if ((vars->y_idx == 0 || vars->y_idx == vars->map_y - 1)
				&& str[vars->x_idx] != '1')
			{
				vars->err_msg = "No surrounding wall";
				return (0);
			}
			else if (str[0] != '1' || str[vars->map_x - 1] != '1')
			{
				vars->err_msg = "No surrounding wall";
				return (0);
			}
			else if (str[vars->x_idx] != '1' && str[vars->x_idx] != '0'
				&& str[vars->x_idx] != 'C' && str[vars->x_idx] != 'E'
				&& str[vars->x_idx] != 'P')
			{
				vars->err_msg = "No correct Character";
				return (0);
			}
			vars->x_idx++;
		}
		vars->y_idx++;
	}
	return (1);
}

int	is_correct_count(t_vars *vars)
{
	if (vars->play_str_cnt != 1)
	{
		vars->err_msg = "We need One Player";
		return (0);
	}
	else if (vars->exit_cnt != 1)
	{
		vars->err_msg = "We need One Exit";
		return (0);
	}
	else if (vars->coll_cnt < 1)
	{
		vars->err_msg = "At least 1 collection is required";
		return (0);
	}
	return (1);
}
