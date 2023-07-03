/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 20:30:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_draw_xpoints(t_vars *vars, t_ray *r)
{
	if (r->side == X_SIDE)
	{
		r->perp_wall_dist = (r->cur_x - vars->pos_x \
			+ (1 - r->step_x) / 2) / r->raydir_x;
		r->wall_x = vars->pos_y + r->perp_wall_dist * r->raydir_y;
	}
	else if (r->side == Y_SIDE)
	{
		r->perp_wall_dist = (r->cur_y - vars->pos_y \
			+ (1 - r->step_y) / 2) / r->raydir_y;
		r->wall_x = vars->pos_x + r->perp_wall_dist * r->raydir_x;
	}
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)vars->texture->img_width);
	if ((r->side == X_SIDE && r->raydir_x < 0) \
		|| (r->side == Y_SIDE && r->raydir_y > 0))
		r->tex_x = vars->texture->img_width - r->tex_x -1;
}

void	init_draw_ypoints(t_ray *r)
{
	r->line_height = (int)((SCREEN_HEIGHT / 2) / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + SCREEN_HEIGHT / 2;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}

static void	painting(t_vars *vars, t_ray *r, int x)
{
	if (r->raydir_y < 0 && r->side == Y_SIDE)
		paint_walls(vars, &vars->texture[NO], r, x);
	else if (r->raydir_y > 0 && r->side == Y_SIDE)
		paint_walls(vars, &vars->texture[SO], r, x);
	else if (r->raydir_x < 0 && r->side == X_SIDE)
		paint_walls(vars, &vars->texture[WE], r, x);
	else if (r->raydir_x > 0 && r->side == X_SIDE)
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
		if (vars->new_map[r.cur_y][r.cur_x] == '1')
			painting(vars, &r, x);
	}
	paint_minimap(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (0);
}
