/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/02 16:40:03 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img.addr + (y * vars->img.len + x * (vars->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	paint_player(t_vars *vars, int width, int height)
{
	int	h;
	int	w;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			if ((vars->posX * MINIMAP_SIZE > w && vars->posX * MINIMAP_SIZE < w + 3) && (vars->posY * MINIMAP_SIZE > h && vars->posY * MINIMAP_SIZE < h + 3))
			{
				my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, h + MINIMAP_SIZE / 2, 0xff0000);
			}
		}
	}
}

void	paint_minimap(t_vars *vars, int width, int height)
{
	int	h;
	int	w;
	int	cx;
	int	cy;

	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
		{
			cx = w / MINIMAP_SIZE;
			cy = h / MINIMAP_SIZE;
			if (h == 0 || h == height - 1 || w == 0 || w == width - 1)
				my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, h + MINIMAP_SIZE / 2, 0xff0000);
			else if ((vars->posX * MINIMAP_SIZE > w && vars->posX * MINIMAP_SIZE < w + 3) && (vars->posY * MINIMAP_SIZE > h && vars->posY * MINIMAP_SIZE < h + 3))
				my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, h + MINIMAP_SIZE / 2, 0xff0000);
			else if (vars->new_map[cy][cx] == '1')
				my_mlx_pixel_put(vars, w  + MINIMAP_SIZE / 2, h + MINIMAP_SIZE / 2, 0xa0a0a0);
			else if (vars->new_map[cy][cx] == -1)
				my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, h + MINIMAP_SIZE / 2, vars->ceiling);
			else
				my_mlx_pixel_put(vars, w + MINIMAP_SIZE / 2, h + MINIMAP_SIZE / 2, vars->floor);
		}
	}
}

void	draw_vertical_line(t_vars *vars, int x, int start, int end, int color)
{
	int	y;

	y = start - 1;
	while (++y <= end)
	{
		my_mlx_pixel_put(vars, x, y, color);
	}
}

void	paint_bg(t_vars *vars)
{
	int	w;
	int	h;

	h = -1;
	while (++h < vars->height)
	{
		w = -1;
		while (++w < vars->width)
		{
			if (h < vars->height / 2)
				my_mlx_pixel_put(vars, w, h, vars->ceiling);
			else
				my_mlx_pixel_put(vars, w, h, vars->floor);
		}
	}
}

void	init_player(t_vars *vars)
{
	if (vars->play_pos == 'N')
	{
		vars->p.dirX = 0;
		vars->p.dirY = -1;
		vars->p.planeX = 0.66;
		vars->p.planeY = 0;
	}
	else if (vars->play_pos == 'S')
	{
		vars->p.dirX = 0;
		vars->p.dirY = 1;
		vars->p.planeX = 0.66;
		vars->p.planeY = 0;
	}
	else if (vars->play_pos == 'E')
	{
		vars->p.dirX = 1;
		vars->p.dirY = 0;
		vars->p.planeX = 0;
		vars->p.planeY = 0.66;
	}
	else if (vars->play_pos == 'W')
	{
		vars->p.dirX = -1;
		vars->p.dirY = 0;
		vars->p.planeX = 0;
		vars->p.planeY = 0.66;
	}
}

void	paint_walls(t_vars *vars, t_texture *texture, t_ray r, int x)
{
	int	h;
	int	color;

	r.texStep = 1.0 * vars->texture->img_height / r.lineHeight;
	r.texPos = (r.drawStart - vars->height / 2 + r.lineHeight / 2) * r.texStep;
	// r.texPos = 0;
	h = r.drawStart - 1;
	texture->p = (int *)mlx_get_data_addr(texture->img.ptr, &texture->img.bpp, &texture->img.len, &texture->img.endian);
	while (++h < r.drawEnd)
	{
		r.texY = (int)r.texPos;
		r.texPos += r.texStep;
		// printf("texX: %d, texY: %d, texPos: %f, texStep: %f, idx: %d\n", r.texX, r.texY, r.texPos, r.texStep, texture->img_height * r.texY + r.texX);
		color = texture->p[texture->img_height * r.texY + r.texX];
		my_mlx_pixel_put(vars, x, h, color);
	}
}

void	paint_wall_test(t_vars *vars, t_texture *texture)
{
	for (int i = 0; i < texture->img_height; i++)
	{
		for (int j = 0; j < texture->img_width; j++)
		{
			my_mlx_pixel_put(vars, j, i, texture->colors[i][j]);
		}
	}
}

int	paint_map(t_vars *vars)
{
	int		x;
	t_ray	r;

	mlx_clear_window(vars->mlx, vars->win);
	paint_bg(vars);
	// paint_wall_test(vars, &vars->texture[NO]);
	x = -1;
	while (++x < vars->width)
	{
		r.mapX = (int)vars->posX;
		r.mapY = (int)vars->posY;
		r.camX = 2 * x / (double)(vars->width) - 1;
		r.raydirX = vars->p.dirX + vars->p.planeX * r.camX;
		r.raydirY = vars->p.dirY + vars->p.planeY * r.camX;
		r.deltaDistX = fabs(1 / r.raydirX);
		r.deltaDistY = fabs(1 / r.raydirY);
		if (r.raydirX > 0)
		{
			r.stepX = 1;
			r.sideDistX = (r.mapX + 1 - vars->posX) * r.deltaDistX;
		}	
		else
		{
			r.stepX = -1;
			r.sideDistX = (vars->posX - r.mapX) * r.deltaDistX;
		}
		if (r.raydirY > 0)
		{
			r.stepY = 1;
			r.sideDistY = (r.mapY + 1 - vars->posY) * r.deltaDistY;
		}
		else
		{
			r.stepY = -1;
			r.sideDistY = (vars->posY - r.mapY) * r.deltaDistY;
		}
		r.hit = 0;
		while (!r.hit)
		{
			if (r.sideDistX < r.sideDistY)
			{
				r.sideDistX += r.deltaDistX;
				r.mapX += r.stepX;
				r.side = X_SIDE;
			}
			else
			{
				r.sideDistY += r.deltaDistY;
				r.mapY += r.stepY;
				r.side = Y_SIDE;
			}
			if (vars->new_map[r.mapY][r.mapX] == '1')
				r.hit = 1;
		}
		if (r.side == X_SIDE)
		{
			r.perpWallDist = (r.mapX - vars->posX + (1 - r.stepX) / 2) / r.raydirX;
			r.wallX = vars->posY + r.perpWallDist * r.raydirY;
		}
		else if (r.side == Y_SIDE)
		{
			r.perpWallDist = (r.mapY - vars->posY + (1 - r.stepY) / 2) / r.raydirY;
			r.wallX = vars->posX + r.perpWallDist * r.raydirX;
		}
		r.wallX -= floor(r.wallX);
		// texture x 좌표
		r.texX = (int)(r.wallX * (double)vars->texture->img_width);
		// 텍스쳐 좌우 반전
		if ((r.side == X_SIDE && r.raydirX < 0) || (r.side == Y_SIDE && r.raydirY > 0))
			r.texX = vars->texture->img_width - r.texX -1;
		// 벽 높이
		r.lineHeight = (int)((vars->height / 2) / r.perpWallDist);
		r.drawStart = -r.lineHeight / 2 + vars->height / 2;
		if (r.drawStart < 0)
			r.drawStart = 0;
		r.drawEnd = r.lineHeight / 2 + vars->height / 2;
		if (r.drawEnd >= vars->height)
			r.drawEnd = vars->height - 1;
		// r.texStep = 1.0 * BLOCK_SIZE / r.lineHeight;
		// r.texPos = (r.drawStart - vars->height / 2 + r.lineHeight / 2) * r.texStep;
		// for (int y = r.drawStart; y < r.drawEnd; y++)
		// {
		// 	r.texY = (int)r.texPos 
		// }
		if (vars->new_map[r.mapY][r.mapX] == '1')
		{
			if (r.raydirY < 0 && r.side == Y_SIDE)
			{
				paint_walls(vars, &vars->texture[NO], r, x);
			}
			else if (r.raydirY > 0 && r.side == Y_SIDE)
			{
				paint_walls(vars, &vars->texture[SO], r, x);
			}
			else if (r.raydirX < 0 && r.side == X_SIDE)
			{
				paint_walls(vars, &vars->texture[WE], r, x);
			}
			else if (r.raydirX > 0 && r.side == X_SIDE)
			{
				paint_walls(vars, &vars->texture[EA], r, x);
			}
			// if (r.side == Y_SIDE)
			// 	draw_vertical_line(vars, x, r.drawStart, r.drawEnd, 0x33CCCC);
			// else
			// 	draw_vertical_line(vars, x, r.drawStart, r.drawEnd, 0x66FFFF);
		}
	}
	paint_minimap(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
	// paint_player(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	double	oldDirX;
	double	oldPlaneX;

	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == KEY_W)
	{
		if (vars->new_map[(int)(vars->posY)][(int)(vars->posX + vars->p.dirX * SPEED)] != '1')
			vars->posX += vars->p.dirX * SPEED;
		if (vars->new_map[(int)(vars->posY + vars->p.dirY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY += vars->p.dirY * SPEED;
	}
	else if (keycode == KEY_S)
	{
		if (vars->new_map[(int)(vars->posY)][(int)(vars->posX - vars->p.dirX * SPEED)] != '1')
			vars->posX -= vars->p.dirX * SPEED;
		if (vars->new_map[(int)(vars->posY - vars->p.dirY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY -= vars->p.dirY * SPEED;
	}
		else if (keycode == KEY_D)
	{
		if (vars->new_map[(int)(vars->posY)][(int)(vars->posX + vars->p.planeX * SPEED)] != '1')
			vars->posX += vars->p.planeX * SPEED;
		if (vars->new_map[(int)(vars->posY + vars->p.planeY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY += vars->p.planeY * SPEED;
	}
	else if (keycode == KEY_A)
	{
		if (vars->new_map[(int)(vars->posY)][(int)(vars->posX - vars->p.planeX * SPEED)] != '1')
			vars->posX -= vars->p.planeX * SPEED;
		if (vars->new_map[(int)(vars->posY - vars->p.planeY * SPEED)][(int)(vars->posX)] != '1')
			vars->posY -= vars->p.planeY * SPEED;
	}
	else if (keycode == KEY_LEFT)
	{
		oldDirX = vars->p.dirX;
		vars->p.dirX = vars->p.dirX * cos(vars->angle) + vars->p.dirY * sin(vars->angle);
		vars->p.dirY = -oldDirX * sin(vars->angle) + vars->p.dirY * cos(vars->angle);
		oldPlaneX = vars->p.planeX;
		vars->p.planeX = vars->p.planeX * cos(vars->angle) + vars->p.planeY * sin(vars->angle);
		vars->p.planeY = -oldPlaneX * sin(vars->angle) + vars->p.planeY * cos(vars->angle);
	}
	else if (keycode == KEY_RIGHT)
	{
		oldDirX = vars->p.dirX;
		vars->p.dirX = vars->p.dirX * cos(vars->angle) - vars->p.dirY * sin(vars->angle);
		vars->p.dirY = oldDirX * sin(vars->angle) + vars->p.dirY * cos(vars->angle);
		oldPlaneX = vars->p.planeX;
		vars->p.planeX = vars->p.planeX * cos(vars->angle) - vars->p.planeY * sin(vars->angle);
		vars->p.planeY = oldPlaneX * sin(vars->angle) + vars->p.planeY * cos(vars->angle);
	}
	return (0);
}
