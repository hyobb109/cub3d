/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 23:10:39 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img.addr + (y * vars->img.len + x * (vars->img.bpp / 8));
	*(unsigned int *)dst = color;
}

static void	paint_bg(t_vars *vars)
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

static void	paint_walls(t_vars *vars, t_texture *texture, t_ray *r, int x)
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
		init_raycasting_vars(vars, &r, x);
		init_side_dist(vars, &r);
		raycasting(vars, &r);
		init_perp_dist(vars, &r);
		init_draw_ypoints(&r);
		if (vars->new_map[r.cur_y][r.cur_x] == '1')
			painting(vars, &r, x);
	}
	paint_minimap(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (0);
}
