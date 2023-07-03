/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:34:14 by hyobicho          #+#    #+#             */
/*   Updated: 2023/07/03 17:35:09 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_vars *vars)
{
	if (vars->new_map[(int)(vars->posY)] \
		[(int)(vars->posX + vars->p.dirX * SPEED)] != '1')
		vars->posX += vars->p.dirX * SPEED;
	if (vars->new_map[(int)(vars->posY \
		+ vars->p.dirY * SPEED)][(int)(vars->posX)] != '1')
		vars->posY += vars->p.dirY * SPEED;
}

void	move_down(t_vars *vars)
{
	if (vars->new_map[(int)(vars->posY)] \
		[(int)(vars->posX - vars->p.dirX * SPEED)] != '1')
		vars->posX -= vars->p.dirX * SPEED;
	if (vars->new_map[(int)(vars->posY \
		- vars->p.dirY * SPEED)][(int)(vars->posX)] != '1')
		vars->posY -= vars->p.dirY * SPEED;
}

void	move_left(t_vars *vars)
{
	if (vars->new_map[(int)(vars->posY)]
		[(int)(vars->posX + vars->p.planeX * SPEED)] != '1')
		vars->posX += vars->p.planeX * SPEED;
	if (vars->new_map[(int)(vars->posY \
		+ vars->p.planeY * SPEED)][(int)(vars->posX)] != '1')
		vars->posY += vars->p.planeY * SPEED;
}

void	move_right(t_vars *vars)
{
	if (vars->new_map[(int)(vars->posY)] \
		[(int)(vars->posX - vars->p.planeX * SPEED)] != '1')
		vars->posX -= vars->p.planeX * SPEED;
	if (vars->new_map[(int)(vars->posY \
		- vars->p.planeY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY -= vars->p.planeY * SPEED;
}
