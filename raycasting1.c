/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 16:29:42 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//init.c로 옮기기
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

//init.c로 옮기기
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

void	init_draw_xpoints(t_vars *vars, t_ray *r)
{
	if (r->side == X_SIDE)
	{
		r->perpWallDist = (r->mapX - vars->posX \
			+ (1 - r->stepX) / 2) / r->raydirX;
		r->wallX = vars->posY + r->perpWallDist * r->raydirY;
	}
	else if (r->side == Y_SIDE)
	{
		r->perpWallDist = (r->mapY - vars->posY \
			+ (1 - r->stepY) / 2) / r->raydirY;
		r->wallX = vars->posX + r->perpWallDist * r->raydirX;
	}
	r->wallX -= floor(r->wallX);
	r->texX = (int)(r->wallX * (double)vars->texture->img_width);// texture x 좌표
	if ((r->side == X_SIDE && r->raydirX < 0) \
		|| (r->side == Y_SIDE && r->raydirY > 0))
		r->texX = vars->texture->img_width - r->texX -1;// 텍스쳐 좌우 반전
}

void	init_draw_ypoints(t_ray *r)// 벽 높이
{
	r->lineHeight = (int)((SCREEN_HEIGHT / 2) / r->perpWallDist);
	r->drawStart = -r->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (r->drawEnd >= SCREEN_HEIGHT)
		r->drawEnd = SCREEN_HEIGHT - 1;
}
