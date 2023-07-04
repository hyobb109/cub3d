/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:13:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/04 13:16:53 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_surrounded(t_vars *vars, int x, int y, int i)
{
	const int	dy[4] = {-1, 1, 0, 0};
	const int	dx[4] = {0, 0, -1, 1};
	int			cx;
	int			cy;

	while (++i < 4)
	{
		cx = x + dx[i];
		cy = y + dy[i];
		if (cx < 0 || cy < 0 || cx >= vars->map_x || cy >= vars->map_y)
			continue ;
		if (vars->new_map[cy][cx] != -1 && vars->new_map[cy][cx] != '1')
			print_error_exit("Map is not surrounded by wall");
	}
}

static void	check_wall(t_vars *vars)
{
	int			x;
	int			y;

	y = -1;
	while (++y < vars->map_y)
	{
		x = -1;
		while (++x < vars->map_x)
		{
			if (vars->new_map[y][x] == -1)
				is_surrounded(vars, x, y, -1);
		}
	}
}

static void	check_filename(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = i;
		while (++j < 4)
		{
			if (!ft_strcmp(vars->texture[i].file_name,
					vars->texture[j].file_name))
				print_error_exit("Texture file name is duplicated");
		}
	}
}

void	check_mapfile(t_vars *vars)
{
	int		cnt;
	char	*str;
	t_map	*map;

	cnt = 0;
	map = 0;
	str = get_next_line(vars->fd);
	if (!str)
		print_error_exit("No return value from GNL");
	while (str)
	{
		cnt = count_data(vars, str, cnt);
		if (cnt == 6)
			break ;
		str = get_next_line(vars->fd);
	}
	if (cnt != 6)
		print_error_exit("Element error");
	check_filename(vars);
	str = init_map_head(vars, &map);
	measure_map_size(vars, map, str);
	init_map(vars, map);
	check_wall(vars);
}
