/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 17:43:18 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img.addr + (y * vars->img.len + x * (vars->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	paint_bg(t_vars *vars)
{
	int	w;
	int	h;

	h = -1;
	while (++h < SCREEN_HEIGHT)
	{
		w = -1;
		while (++w < SCREEN_WIDTH)
		{
			if (h < SCREEN_HEIGHT / 2)
				my_mlx_pixel_put(vars, w, h, vars->ceiling);
			else
				my_mlx_pixel_put(vars, w, h, vars->floor);
		}
	}
}

void	paint_walls(t_vars *vars, t_texture *texture, t_ray *r, int x)
{
	int	y;
	int	color;

	r->texStep = 1.0 * vars->texture->img_height / r->lineHeight;
	r->texPos = (r->drawStart - SCREEN_HEIGHT / 2 \
		+ r->lineHeight / 2) * r->texStep;
	y = r->drawStart - 1;
	texture->colors = (int *)mlx_get_data_addr(texture->img.ptr, \
		&texture->img.bpp, &texture->img.len, &texture->img.endian);
	while (++y < r->drawEnd)
	{
		r->texY = (int)r->texPos;
		r->texPos += r->texStep;
		color = texture->colors[texture->img_height * r->texY + r->texX];
		my_mlx_pixel_put(vars, x, y, color);
	}
}
