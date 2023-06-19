/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:44:59 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/19 20:16:46 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_vars *vars)
{
	int		i;
	int		j;
	int		max;

	i = 0;
	max = -1;
	while (vars->new_map[i])
	{
		j = 0;
		while(vars->new_map[i][j])
		{
			if (ft_isblank(vars->new_map[i][j]))
			{
				vars->new_map[i][j] = -1;
			}
			j++;
			if (j > max)
				max = j;
		}
		i++;
	}
	vars->map_x = max;
	vars->map_y = i;
	printf("==== map ====\n");
	print_strs(vars->new_map);
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
