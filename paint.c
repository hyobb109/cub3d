/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 20:29:46 by yunjcho          ###   ########.fr       */
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

	r->tex_step = 1.0 * vars->texture->img_height / r->line_height;
	r->tex_pos = (r->draw_start - SCREEN_HEIGHT / 2 \
		+ r->line_height / 2) * r->tex_step;
	y = r->draw_start - 1;
	texture->colors = (int *)mlx_get_data_addr(texture->img.ptr, \
		&texture->img.bpp, &texture->img.len, &texture->img.endian);
	while (++y < r->draw_end)
	{
		r->tex_y = (int)r->tex_pos;
		r->tex_pos += r->tex_step;
		color = texture->colors[texture->img_height * r->tex_y + r->tex_x];
		my_mlx_pixel_put(vars, x, y, color);
	}
}
