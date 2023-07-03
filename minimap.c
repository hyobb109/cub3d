/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:37:16 by hyobicho          #+#    #+#             */
/*   Updated: 2023/07/03 20:30:16 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_redrange(t_vars *vars, int w, int h)
{
	int	width;
	int	height;

	width = vars->map_x * MINIMAP_SIZE;
	height = vars->map_y * MINIMAP_SIZE;
	if (((vars->pos_x * MINIMAP_SIZE > w \
		&& vars->pos_x * MINIMAP_SIZE < w + 3) \
		&& (vars->pos_y * MINIMAP_SIZE > h \
		&& vars->pos_y * MINIMAP_SIZE < h + 3)) \
		|| h == 0 || h == height - 1 || w == 0 || w == width - 1)
		return (1);
	return (0);
}

static void	painting_minimap(t_vars *vars, int w, int h)
{
	int	cx;
	int	cy;

	cx = w / MINIMAP_SIZE;
	cy = h / MINIMAP_SIZE;
	if (is_redrange(vars, w, h))
		my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, \
		h + MINIMAP_SIZE / 2, 0xff0000);
	else if (vars->new_map[cy][cx] == '1')
		my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, \
			h + MINIMAP_SIZE / 2, 0xa0a0a0);
	else if (vars->new_map[cy][cx] == -1)
		my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, \
			h + MINIMAP_SIZE / 2, vars->ceiling);
	else
		my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, \
			h + MINIMAP_SIZE / 2, vars->floor);
}

void	paint_minimap(t_vars *vars, int width, int height)
{
	int	h;
	int	w;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			painting_minimap(vars, w, h);
		}
	}
}
