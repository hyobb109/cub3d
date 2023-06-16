/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:44:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 17:45:30 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_vars *vars)
{
	int		y_idx;
	char	*str;

	vars->new_map = (char **)malloc(sizeof(char *) * (vars->map_y + 1));
	if (!vars->new_map)
	{
		free_matrix(vars->new_map);
		return ;
	}
	y_idx = 0;
	vars->hei = 0;
	while (1)
	{
		str = get_next_line(vars->fd);
		if (!str)
			break ;
		vars->new_map[y_idx] = ft_strtrim(str, "\n");
		count_stuff(vars, vars->new_map[y_idx], y_idx);
		y_idx++;
		free(str);
	}
	vars->new_map[y_idx] = 0;
	close(vars->fd);
}

char	**free_matrix(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
	return (0);
}
