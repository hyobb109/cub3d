/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:13:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/19 21:04:47 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	is_rectangle(t_vars *vars)
// {
// 	int		str_len;
// 	int		y_idx;

// 	str_len = 0;
// 	y_idx = 0;
// 	while (y_idx < vars->map_y && vars->new_map[y_idx])
// 	{
// 		str_len = ft_strlen(vars->new_map[y_idx]);
// 		if (vars->map_x != str_len)
// 		{
// 			vars->err_msg = "Invalid map dimension";
// 			return (0);
// 		}
// 		y_idx++;
// 	}
// 	return (1);
// }

void	is_surrounded(t_vars *vars, char **str, int h)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != '1' && str[i][j] != '0' && str[i][j] != 'N' && str[i][j] != 'S' && str[i][j] != 'E' && str[i][j] != 'W')
			{
				print_error_exit("Invalid map character");
			}
			if (h == 0 || h == vars->map_y - 1)
			{
				if (str[i][j] != '1')
					print_error_exit("Not surrounded by walls 1");
			}
			else if (j == 0 || j == (int)(ft_strlen(str[i]) - 1))
			{
				if (str[i][j] != '1')
					print_error_exit("Not surrounded by walls 2");
			}
			j++;
		}
		i++;
	}
}

void	validate_map(t_vars *vars)
{
	char	**tmp;
	int		h;

	h = 0;
	while (h < vars->map_y)
	{
		tmp = ft_split(vars->new_map[h], -1);
		is_surrounded(vars, tmp, h);
		h++;
	}
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
