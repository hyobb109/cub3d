/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 16:34:43 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	adjust_pos_range(t_vars *vars)
// {
// 	if (vars->new_map[(int)(vars->posY + 0.01)][(int)vars->posX] == '1')
// 		vars->posY -= 0.01;
// 	else if (vars->new_map[(int)(vars->posY - 0.01)][(int)vars->posX] == '1')
// 		vars->posY += 0.01;
// 	else if (vars->new_map[(int)vars->posY][(int)(vars->posX + 0.01)] == '1')
// 		vars->posX -= 0.01;
// 	else if (vars->new_map[(int)vars->posY][(int)(vars->posX - 0.01)] == '1')
// 		vars->posX += 0.01;
// }

void	painting(t_vars *vars, t_ray *r, int x)
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
	adjust_pos_range(vars);
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
