/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:13:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 13:47:01 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	free_matrix(visited);
}
