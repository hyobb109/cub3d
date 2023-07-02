/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:13:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/02 19:24:54 by hyobicho         ###   ########.fr       */
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

void	is_surrounded(t_vars *vars, char **visited)
{
	const int	dy[4] = {-1, 1, 0, 0};
	const int	dx[4] = {0, 0, -1, 1};
	int			i;
	int			x;
	int			y;
	int			cx;
	int			cy;
	
	y = -1;
	while (++y < vars->map_y)
	{
		x = -1;
		while (++x < vars->map_x)
		{
			if (vars->new_map[y][x] == -1)
			{
				i = -1;
				while (++i < 4)
				{
					cx = x + dx[i];
					cy = y + dy[i];
					if (cx < 0 || cy < 0 || cx >= vars->map_x || cy >= vars->map_y)
						continue ;
					if (vars->new_map[cy][cx] != -1 && vars->new_map[cy][cx] != '1')
						print_error_exit("Map is not surrounded by wall");
					visited[y][x] = 'T';
				}
			}
		}
	}
}

char	**make_visit_array(t_vars *vars)
{
	int		i;
	int		j;
	char	**check_array;

	j = 0;
	check_array = (char **)malloc(sizeof(char *) * (vars->map_y + 1));
	while (j < vars->map_y)
	{
		check_array[j] = (char *)malloc(sizeof(char) * vars->map_x + 1);
		i = 0;
		while (i < vars->map_x)
		{
			// if (vars->new_map[j][i] != -1)
			// 	check_array[j][i] = vars->new_map[j][i];
			// else
				check_array[j][i] = 'F';
			i++;
		}
		check_array[j][i] = '\0';
		j++;
	}
	check_array[j] = 0;
	return (check_array);
}

void	validate_map(t_vars *vars)
{
	char	**visited;

	visited = make_visit_array(vars);
	is_surrounded(vars, visited);
	vars->width = SCREEN_WIDTH;
	vars->height = SCREEN_HEIGHT;
}

int	is_correct_count(t_vars *vars)
{
	if (vars->exit_cnt != 1)
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
