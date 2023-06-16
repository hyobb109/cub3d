/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:08:16 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 16:20:25 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_continued(t_vars *vars)
{
	if (vars->cur_x < 0 || vars->cur_y < 0
		|| vars->cur_x >= vars->map_x
		|| vars->cur_y >= vars->map_y
		|| vars->new_map[vars->cur_y][vars->cur_x] == '1')
		return (1);
	return (0);
}

int	is_stuff(t_vars *vars)
{
	if (vars->new_map[vars->cur_y][vars->cur_x] == '0'
		|| vars->new_map[vars->cur_y][vars->cur_x] == 'C'
		|| vars->new_map[vars->cur_y][vars->cur_x] == 'P'
		|| vars->new_map[vars->cur_y][vars->cur_x] == 'E')
		return (1);
	return (0);
}
