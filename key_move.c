/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:34:14 by hyobicho          #+#    #+#             */
/*   Updated: 2023/07/03 20:30:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_vars *vars)
{
	if (vars->new_map[(int)(vars->pos_y)] \
		[(int)(vars->pos_x + vars->p.dir_x * SPEED)] != '1')
		vars->pos_x += vars->p.dir_x * SPEED;
	if (vars->new_map[(int)(vars->pos_y \
		+ vars->p.dir_y * SPEED)][(int)(vars->pos_x)] != '1')
		vars->pos_y += vars->p.dir_y * SPEED;
}

void	move_down(t_vars *vars)
{
	if (vars->new_map[(int)(vars->pos_y)] \
		[(int)(vars->pos_x - vars->p.dir_x * SPEED)] != '1')
		vars->pos_x -= vars->p.dir_x * SPEED;
	if (vars->new_map[(int)(vars->pos_y \
		- vars->p.dir_y * SPEED)][(int)(vars->pos_x)] != '1')
		vars->pos_y -= vars->p.dir_y * SPEED;
}

void	move_left(t_vars *vars)
{
	if (vars->new_map[(int)(vars->pos_y)]
		[(int)(vars->pos_x + vars->p.plane_x * SPEED)] != '1')
		vars->pos_x += vars->p.plane_x * SPEED;
	if (vars->new_map[(int)(vars->pos_y \
		+ vars->p.plane_y * SPEED)][(int)(vars->pos_x)] != '1')
		vars->pos_y += vars->p.plane_y * SPEED;
}

void	move_right(t_vars *vars)
{
	if (vars->new_map[(int)(vars->pos_y)] \
		[(int)(vars->pos_x - vars->p.plane_x * SPEED)] != '1')
		vars->pos_x -= vars->p.plane_x * SPEED;
	if (vars->new_map[(int)(vars->pos_y \
		- vars->p.plane_y * SPEED)][(int)(vars->pos_x)] != '1')
			vars->pos_y -= vars->p.plane_y * SPEED;
}
