/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:35:21 by hyobicho          #+#    #+#             */
/*   Updated: 2023/07/03 17:38:26 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_vars *vars)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = vars->p.dirX;
	vars->p.dirX = vars->p.dirX \
		* cos(vars->angle) + vars->p.dirY * sin(vars->angle);
	vars->p.dirY = -olddir_x \
		* sin(vars->angle) + vars->p.dirY * cos(vars->angle);
	oldplane_x = vars->p.planeX;
	vars->p.planeX = vars->p.planeX \
		* cos(vars->angle) + vars->p.planeY * sin(vars->angle);
	vars->p.planeY = -oldplane_x \
		* sin(vars->angle) + vars->p.planeY * cos(vars->angle);
}

void	rotate_right(t_vars *vars)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = vars->p.dirX;
	vars->p.dirX = vars->p.dirX \
		* cos(vars->angle) - vars->p.dirY * sin(vars->angle);
	vars->p.dirY = olddir_x \
		* sin(vars->angle) + vars->p.dirY * cos(vars->angle);
	oldplane_x = vars->p.planeX;
	vars->p.planeX = vars->p.planeX
		* cos(vars->angle) - vars->p.planeY * sin(vars->angle);
	vars->p.planeY = oldplane_x
		* sin(vars->angle) + vars->p.planeY * cos(vars->angle);
}
