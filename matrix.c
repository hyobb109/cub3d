/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:44:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 20:30:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_lst(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map->next;
		free(map->str);
		free(map);
		map = tmp;
	}
}

static void	init_map_line(t_vars *vars, t_map *tmp, int y_idx)
{
	int		x_idx;

	x_idx = -1;
	while (++x_idx < vars->map_x)
	{
		if (x_idx >= tmp->width)
			vars->new_map[y_idx][x_idx] = -1;
		else if ((y_idx == 0 || y_idx == vars->map_y - 1 \
		|| x_idx == 0 || x_idx == tmp->width - 1) && tmp->str[x_idx] == '0')
			print_error_exit("Map is not surrounded by wall");
		else
			vars->new_map[y_idx][x_idx] = tmp->str[x_idx];
		if (x_idx < tmp->width && tmp->str[x_idx] == vars->play_pos)
		{
			vars->pos_x = x_idx + 0.5;
			vars->pos_y = y_idx + 0.5;
		}
	}
	vars->new_map[y_idx][x_idx] = '\0';
}

void	init_map(t_vars *vars, t_map *map)
{
	int		y_idx;
	t_map	*tmp;

	tmp = map;
	vars->new_map = (char **)malloc(sizeof(char *) * (vars->map_y + 1));
	if (!vars->new_map)
		print_error_exit("malloc error");
	y_idx = -1;
	while (++y_idx < vars->map_y)
	{
		vars->new_map[y_idx] = (char *)malloc(sizeof(char) * (vars->map_x + 1));
		if (!vars->new_map[y_idx])
			print_error_exit("malloc error");
		init_map_line(vars, tmp, y_idx);
		tmp = tmp->next;
	}
	vars->new_map[y_idx] = 0;
	free_lst(map);
}

void	free_matrix(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}
