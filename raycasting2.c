/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 22:59:13 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_perp_dist(t_vars *vars, t_ray *r)
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

void	raycasting(t_vars *vars, t_ray *r)
{
	r->hit = 0;
	while (!r->hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->cur_x += r->step_x;
			r->side = X_SIDE;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->cur_y += r->step_y;
			r->side = Y_SIDE;
		}
		if (vars->new_map[r->cur_y][r->cur_x] == '1')
			r->hit = 1;
	}
}
