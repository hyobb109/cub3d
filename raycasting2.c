/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 17:44:18 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	r->texX = (int)(r->wallX * (double)vars->texture->img_width);
	if ((r->side == X_SIDE && r->raydirX < 0) \
		|| (r->side == Y_SIDE && r->raydirY > 0))
		r->texX = vars->texture->img_width - r->texX -1;
}

void	init_draw_ypoints(t_ray *r)
{
	r->lineHeight = (int)((SCREEN_HEIGHT / 2) / r->perpWallDist);
	r->drawStart = -r->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (r->drawStart < 0)
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (r->drawEnd >= SCREEN_HEIGHT)
		r->drawEnd = SCREEN_HEIGHT - 1;
}

static void	painting(t_vars *vars, t_ray *r, int x)
{
	if (r->raydirY < 0 && r->side == Y_SIDE)
		paint_walls(vars, &vars->texture[NO], r, x);
	else if (r->raydirY > 0 && r->side == Y_SIDE)
		paint_walls(vars, &vars->texture[SO], r, x);
	else if (r->raydirX < 0 && r->side == X_SIDE)
		paint_walls(vars, &vars->texture[WE], r, x);
	else if (r->raydirX > 0 && r->side == X_SIDE)
		paint_walls(vars, &vars->texture[EA], r, x);
}

int	paint_map(t_vars *vars)
{
	int		x;
	t_ray	r;

	mlx_clear_window(vars->mlx, vars->win);
	paint_bg(vars);
	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		init_raycasting_vars1(vars, &r, x);
		init_raycasting_vars2(vars, &r);
		raycasting(vars, &r);
		init_draw_xpoints(vars, &r);
		init_draw_ypoints(&r);
		if (vars->new_map[r.mapY][r.mapX] == '1')
			painting(vars, &r, x);
	}
	paint_minimap(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (0);
}
