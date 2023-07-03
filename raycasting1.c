/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 20:30:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dirplane(t_vars *vars, int idx)
{
	const double	dir_x[4] = {0.0, 0.0, -1.0, 1.0};
	const double	dir_y[4] = {-1.0, 1.0, 0.0, 0.0};
	const double	plane_x[4] = {0.66, -0.66, 0.0, 0.0};
	const double	plane_y[4] = {0.0, 0.0, -0.66, 0.66};

	vars->p.dir_x = dir_x[idx];
	vars->p.dir_y = dir_y[idx];
	vars->p.plane_x = plane_x[idx];
	vars->p.plane_y = plane_y[idx];
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
	r->cur_x = (int)vars->pos_x;
	r->cur_y = (int)vars->pos_y;
	r->cam_x = 2 * x / (double)(SCREEN_WIDTH) - 1;
	r->raydir_x = vars->p.dir_x + vars->p.plane_x * r->cam_x;
	r->raydir_y = vars->p.dir_y + vars->p.plane_y * r->cam_x;
	r->delta_dist_x = fabs(1 / r->raydir_x);
	r->delta_dist_y = fabs(1 / r->raydir_y);
}

void	init_raycasting_vars2(t_vars *vars, t_ray *r)
{
	if (r->raydir_x > 0)
	{
		r->step_x = 1;
		r->side_dist_x = (r->cur_x + 1 - vars->pos_x) * r->delta_dist_x;
	}	
	else
	{
		r->step_x = -1;
		r->side_dist_x = (vars->pos_x - r->cur_x) * r->delta_dist_x;
	}
	if (r->raydir_y > 0)
	{
		r->step_y = 1;
		r->side_dist_y = (r->cur_y + 1 - vars->pos_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = -1;
		r->side_dist_y = (vars->pos_y - r->cur_y) * r->delta_dist_y;
	}
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
