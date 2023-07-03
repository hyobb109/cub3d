/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 16:25:55 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img.addr + (y * vars->img.len + x * (vars->img.bpp / 8));
	*(unsigned int *)dst = color;
}

static int	is_redrange(t_vars *vars, int w, int h)
{
	int	width;
	int	height;

	width = vars->map_x * MINIMAP_SIZE;
	height = vars->map_y * MINIMAP_SIZE;
	if (((vars->posX * MINIMAP_SIZE > w \
		&& vars->posX * MINIMAP_SIZE < w + 3) \
		&& (vars->posY * MINIMAP_SIZE > h \
		&& vars->posY * MINIMAP_SIZE < h + 3)) \
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

void	adjust_pos_range(t_vars *vars)
{
	if (vars->new_map[(int)(vars->posY + 0.01)][(int)vars->posX] == '1')
		vars->posY -= 0.01;
	else if (vars->new_map[(int)(vars->posY - 0.01)][(int)vars->posX] == '1')
		vars->posY += 0.01;
	else if (vars->new_map[(int)vars->posY][(int)(vars->posX + 0.01)] == '1')
		vars->posX -= 0.01;
	else if (vars->new_map[(int)vars->posY][(int)(vars->posX - 0.01)] == '1')
		vars->posX += 0.01;
}

int	key_hook(int keycode, t_vars *vars)
{
	double	olddir_x;
	double	oldplane_x;

	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == KEY_W)
	{
		if (vars->new_map[(int)(vars->posY)] \
			[(int)(vars->posX + vars->p.dirX * SPEED)] != '1')
			vars->posX += vars->p.dirX * SPEED;
		if (vars->new_map[(int)(vars->posY \
			+ vars->p.dirY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY += vars->p.dirY * SPEED;
	}
	else if (keycode == KEY_S)
	{
		if (vars->new_map[(int)(vars->posY)] \
			[(int)(vars->posX - vars->p.dirX * SPEED)] != '1')
			vars->posX -= vars->p.dirX * SPEED;
		if (vars->new_map[(int)(vars->posY \
			- vars->p.dirY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY -= vars->p.dirY * SPEED;
	}
	else if (keycode == KEY_D)
	{
		if (vars->new_map[(int)(vars->posY)]
			[(int)(vars->posX + vars->p.planeX * SPEED)] != '1')
			vars->posX += vars->p.planeX * SPEED;
		if (vars->new_map[(int)(vars->posY \
			+ vars->p.planeY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY += vars->p.planeY * SPEED;
	}
	else if (keycode == KEY_A)
	{
		if (vars->new_map[(int)(vars->posY)] \
			[(int)(vars->posX - vars->p.planeX * SPEED)] != '1')
			vars->posX -= vars->p.planeX * SPEED;
		if (vars->new_map[(int)(vars->posY \
			- vars->p.planeY * SPEED)][(int)(vars->posX)] != '1')
				vars->posY -= vars->p.planeY * SPEED;
	}
	else if (keycode == KEY_LEFT)
	{
		olddir_x = vars->p.dirX;
		vars->p.dirX = vars->p.dirX \
			* cos(vars->angle) + vars->p.dirY * sin(vars->angle);
		vars->p.dirY = -olddir_x \
			* sin(vars->angle) + vars->p.dirY * cos(vars->angle);
		oldplane_x = vars->p.planeX;
		vars->p.planeX = vars->p.planeX \
			* cos(vars->angle) + vars->p.planeY * sin(vars->angle);
		vars->p.planeY = -oldplane_x \
			* sin(vars->angle) + vars->p.planeY * cos(vars->angle);
	}
	else if (keycode == KEY_RIGHT)
	{
		olddir_x = vars->p.dirX;
		vars->p.dirX = vars->p.dirX \
			* cos(vars->angle) - vars->p.dirY * sin(vars->angle);
		vars->p.dirY = olddir_x \
			* sin(vars->angle) + vars->p.dirY * cos(vars->angle);
		oldplane_x = vars->p.planeX;
		vars->p.planeX = vars->p.planeX
			* cos(vars->angle) - vars->p.planeY * sin(vars->angle);
		vars->p.planeY = oldplane_x
			* sin(vars->angle) + vars->p.planeY * cos(vars->angle);
	}
	adjust_pos_range(vars);
	return (0);
}
