/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 17:32:32 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dirplane(t_vars *vars, int idx)
{
	const double	dir_x[4] = {0.0, 0.0, -1.0, 1.0};
	const double	dir_y[4] = {-1.0, 1.0, 0.0, 0.0};
	const double	plane_x[4] = {0.66, -0.66, 0.0, 0.0};
	const double	plane_y[4] = {0.0, 0.0, -0.66, 0.66};

	vars->p.dirX = dir_x[idx];
	vars->p.dirY = dir_y[idx];
	vars->p.planeX = plane_x[idx];
	vars->p.planeY = plane_y[idx];
}

void	init_player(t_vars *vars)
{
	if (vars->play_pos == 'N')
		init_dirplane(vars, 0);
	else if (vars->play_pos == 'S')
		init_dirplane(vars, 1);
	else if (vars->play_pos == 'W')
		init_dirplane(vars, 2);
	else if (vars->play_pos == 'E')
		init_dirplane(vars, 3);
}

void	init_raycasting_vars1(t_vars *vars, t_ray *r, int x)
{
	r->mapX = (int)vars->posX;
	r->mapY = (int)vars->posY;
	r->camX = 2 * x / (double)(SCREEN_WIDTH) - 1;
	r->raydirX = vars->p.dirX + vars->p.planeX * r->camX;
	r->raydirY = vars->p.dirY + vars->p.planeY * r->camX;
	r->deltaDistX = fabs(1 / r->raydirX);
	r->deltaDistY = fabs(1 / r->raydirY);
}

void	init_raycasting_vars2(t_vars *vars, t_ray *r)
{
	if (r->raydirX > 0)
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1 - vars->posX) * r->deltaDistX;
	}	
	else
	{
		r->stepX = -1;
		r->sideDistX = (vars->posX - r->mapX) * r->deltaDistX;
	}
	if (r->raydirY > 0)
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1 - vars->posY) * r->deltaDistY;
	}
	else
	{
		r->stepY = -1;
		r->sideDistY = (vars->posY - r->mapY) * r->deltaDistY;
	}
}

void	raycasting(t_vars *vars, t_ray *r)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = X_SIDE;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = Y_SIDE;
		}
		if (vars->new_map[r->mapY][r->mapX] == '1')
			r->hit = 1;
	}
}
