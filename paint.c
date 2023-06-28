/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/28 19:44:22 by yunjcho          ###   ########.fr       */
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
			if ((vars->posX * MINIMAP_SIZE > w && vars->posX * MINIMAP_SIZE < w + MINIMAP_SIZE) && (vars->posY * MINIMAP_SIZE > h && vars->posY * MINIMAP_SIZE < h + MINIMAP_SIZE))
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
				my_mlx_pixel_put(vars, w, h, 0xff0000);
			else if (vars->new_map[cy][cx] == '1')
				my_mlx_pixel_put(vars, w, h, 0xa0a0a0);
			// else if ((vars->posX * MINIMAP_SIZE > w && vars->posX * MINIMAP_SIZE < w + MINIMAP_SIZE / 2) && (vars->posY * MINIMAP_SIZE > h && vars->posY * MINIMAP_SIZE < h + MINIMAP_SIZE / 2))
			// 	my_mlx_pixel_put(vars, w, h, 0xff0000);
			else if (vars->new_map[cy][cx] == -1)
				my_mlx_pixel_put(vars, w, h, vars->ceiling);
			else
				my_mlx_pixel_put(vars, w, h, vars->floor);
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

int	paint_map(t_vars *vars)
{
	int		x;
	t_ray	r;
	paint_bg(vars);
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
		}
		else if (r.side == Y_SIDE)
		{
			r.perpWallDist = (r.mapY - vars->posY + (1 - r.stepY) / 2) / r.raydirY;
		}
		r.lineHeight = (int)((vars->height / 2) / r.perpWallDist);
		r.drawStart = -r.lineHeight / 2 + vars->height / 2;
		if (r.drawStart < 0)
			r.drawStart = 0;
		r.drawEnd = r.lineHeight / 2 + vars->height / 2;
		if (r.drawEnd >= vars->height)
			r.drawEnd = vars->height - 1;
		if (vars->new_map[r.mapY][r.mapX] == '1')
		{
			if (r.side == Y_SIDE)
				draw_vertical_line(vars, x, r.drawStart, r.drawEnd, 0x33CCCC);
			else
				draw_vertical_line(vars, x, r.drawStart, r.drawEnd, 0x66FFFF);
		}
	}
	paint_minimap(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
	paint_player(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
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
		if (vars->new_map[(int)(vars->posY)][(int)(vars->posX + vars->p.dirX * 0.1)] != '1')
		{
			printf("*[%d][%d] = %c\n",(int)(vars->posY),(int)(vars->posX + vars->p.dirX * 0.1), vars->new_map[(int)(vars->posY)][(int)(vars->posX + vars->p.dirX * 0.1)]);
			vars->posX += vars->p.dirX * 0.1;
		}
		if (vars->new_map[(int)(vars->posY + vars->p.dirY * 0.1)][(int)(vars->posX)] != '1')
		{
			printf("**[%d][%d] = %c\n",(int)(vars->posY),(int)(vars->posX + vars->p.dirX * 0.1), vars->new_map[(int)(vars->posY)][(int)(vars->posX + vars->p.dirX * 0.1)]);
			vars->posY += vars->p.dirY * 0.1;
		}
	}
	else if (keycode == KEY_S)
	{
		if (vars->new_map[(int)(vars->posY)][(int)(vars->posX - vars->p.dirX * 0.1)] != '1')
		{
			printf("***[%d][%d] = %c\n",(int)(vars->posY),(int)(vars->posX + vars->p.dirX * 0.1), vars->new_map[(int)(vars->posY)][(int)(vars->posX + vars->p.dirX * 0.1)]);
			vars->posX -= vars->p.dirX * 0.1;
		}
		if (vars->new_map[(int)(vars->posY - vars->p.dirY * 0.1)][(int)(vars->posX)] != '1')
		{
			printf("****[%d][%d] = %c\n",(int)(vars->posY),(int)(vars->posX + vars->p.dirX * 0.1), vars->new_map[(int)(vars->posY)][(int)(vars->posX + vars->p.dirX * 0.1)]);
			vars->posY -= vars->p.dirY * 0.1;
		}
	}
	else if (keycode == KEY_A)
	{
		oldDirX = vars->p.dirX;
		vars->p.dirX = vars->p.dirX * cos(30 * PI / 180) + vars->p.dirY * sin(30 * PI / 180);
		vars->p.dirY = -oldDirX * sin(30 * PI / 180) + vars->p.dirY * cos(30 * PI / 180);
		oldPlaneX = vars->p.planeX;
		vars->p.planeX = vars->p.planeX * cos(30 * PI / 180) + vars->p.planeY * sin(30 * PI / 180);
		vars->p.planeY = -oldPlaneX * sin(30 * PI / 180) + vars->p.planeY * cos(30 * PI / 180);
	}
	else if (keycode == KEY_D)
	{
		oldDirX = vars->p.dirX;
		vars->p.dirX = vars->p.dirX * cos(30 * PI / 180) - vars->p.dirY * sin(30 * PI / 180);
		vars->p.dirY = oldDirX * sin(30 * PI / 180) + vars->p.dirY * cos(30 * PI / 180);
		oldPlaneX = vars->p.planeX;
		vars->p.planeX = vars->p.planeX * cos(30 * PI / 180) - vars->p.planeY * sin(30 * PI / 180);
		vars->p.planeY = oldPlaneX * sin(30 * PI / 180) + vars->p.planeY * cos(30 * PI / 180);
	}
	return (0);
}
