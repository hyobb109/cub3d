/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:35:21 by hyobicho          #+#    #+#             */
/*   Updated: 2023/07/03 20:25:26 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_vars *vars)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = vars->p.dir_x;
	vars->p.dir_x = vars->p.dir_x \
		* cos(vars->angle) + vars->p.dir_y * sin(vars->angle);
	vars->p.dir_y = -olddir_x \
		* sin(vars->angle) + vars->p.dir_y * cos(vars->angle);
	oldplane_x = vars->p.plane_x;
	vars->p.plane_x = vars->p.plane_x \
		* cos(vars->angle) + vars->p.plane_y * sin(vars->angle);
	vars->p.plane_y = -oldplane_x \
		* sin(vars->angle) + vars->p.plane_y * cos(vars->angle);
}

void	rotate_right(t_vars *vars)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = vars->p.dir_x;
	vars->p.dir_x = vars->p.dir_x \
		* cos(vars->angle) - vars->p.dir_y * sin(vars->angle);
	vars->p.dir_y = olddir_x \
		* sin(vars->angle) + vars->p.dir_y * cos(vars->angle);
	oldplane_x = vars->p.plane_x;
	vars->p.plane_x = vars->p.plane_x
		* cos(vars->angle) - vars->p.plane_y * sin(vars->angle);
	vars->p.plane_y = oldplane_x
		* sin(vars->angle) + vars->p.plane_y * cos(vars->angle);
}
