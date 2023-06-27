/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:21:07 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/27 22:02:11 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->img.addr + (y * vars->img.len + x * (vars->img.bpp / 8));
	*(unsigned int *)dst = color;
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
			else if (vars->new_map[cy][cx] == -1)
				my_mlx_pixel_put(vars, w, h, vars->ceiling);
			else if (vars->new_map[cy][cx] == '0')
				my_mlx_pixel_put(vars, w, h, vars->floor);
			else if (vars->new_map[cy][cx] == '1')
				my_mlx_pixel_put(vars, w, h, 0xa0a0a0);
			else if (cy == vars->play_y && cx == vars->play_x)
				my_mlx_pixel_put(vars, w, h, 0x00ffcc);
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

int	paint_map(t_vars *vars)
{
	int x;
	double posX;
	double posY;
	int		mapX;
	int		mapY;
	// player 방향에 맞춰서 초기화
	double dirX = 0;
	double dirY = -1;
	double planeX = 0.66;
	double planeY = 0;
	// 
	double	camX;
	double	raydirX;
	double	raydirY;
	// 처음 벽 충돌까지 거리
	double sideDistX;
	double sideDistY;
	// 벽 충돌까지 거리 변화량
	double deltaDistX;
	double deltaDistY;
	// 플레이어 위치에서 카메라평면과 벽과의 수직거리 계산
	double perpWallDist;
	// 이동방향
	int stepX;
	int stepY;
	// 벽 충돌 여부
	int hit;
	// 충돌한 면
	int side;
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	paint_bg(vars);
	// printf("ceiling: %d %x, floor : %d %x\n", vars->ceiling, vars->floor);
	posX = vars->play_x;
	posY = vars->play_y;
	x = -1;
	while (++x < vars->width)
	{
		mapX = (int)posX;
		mapY = (int)posY;
		camX = 2 * x / (double)(vars->width) - 1;
		raydirX = dirX + planeX * camX;
		raydirY = dirY + planeY * camX;
		deltaDistX = fabs(1 / raydirX);
		deltaDistY = fabs(1 / raydirY);
		if (raydirX > 0)
		{
			stepX = 1;
			sideDistX = (mapX + 1 - posX) * deltaDistX;
		}	
		else
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		if (raydirY > 0)
		{
			stepY = 1;
			sideDistY = (mapY + 1 - posY) * deltaDistY;
		}
		else
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		hit = 0;
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = X_SIDE;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = Y_SIDE;
			}
			if (vars->new_map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == X_SIDE)
		{
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / raydirX;
		}
		else if (side == Y_SIDE)
		{
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / raydirY;
		}
		lineHeight = (int)((vars->height / 2) / perpWallDist);
		drawStart = -lineHeight / 2 + (vars->height / 2) / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + (vars->height / 2) / 2;
		if (drawEnd >= (vars->height / 2))
			drawEnd = (vars->height / 2) - 1;
		if (vars->new_map[mapY][mapX] == '1')
		{
			if (side == Y_SIDE)
				draw_vertical_line(vars, x, drawStart, drawEnd, 0x33CCCC);
			else
				draw_vertical_line(vars, x, drawStart, drawEnd, 0x66FFFF);
		}
	}
	paint_minimap(vars, vars->map_x * MINIMAP_SIZE, vars->map_y * MINIMAP_SIZE);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.ptr, 0, 0);
	return (0);
}

void	check_exit(t_vars *vars)
{
	if (vars->new_map[vars->play_y][vars->play_x] == 'E'
		&& vars->coll_cnt == vars->play_coll_cnt)
	{
		ft_putendl_fd("Congratuation!", 1);
		exit(1);
	}
	else if (vars->new_map[vars->play_y][vars->play_x] == 'C')
	{
		vars->new_map[vars->play_y][vars->play_x] = '0';
		paint_map(vars);
		vars->play_coll_cnt++;
	}
}

void	move_player(t_vars *vars, int keycode)
{
	vars->new_map[vars->play_y][vars->play_x] = '0';
	if (keycode == KEY_W)
		vars->play_y -= 1;
	else if (keycode == KEY_A)
		vars->play_x -= 1;
	else if (keycode == KEY_S)
		vars->play_y += 1;
	else if (keycode == KEY_D)
		vars->play_x += 1;
	vars->new_map[vars->play_y][vars->play_x] = vars->play_pos;
	mlx_clear_window(vars->mlx, vars->win);
	paint_map(vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == KEY_W && vars->play_y > 0
		&& vars->new_map[vars->play_y - 1][vars->play_x] != '1')
		move_player(vars, keycode);
	else if (keycode == KEY_A && vars->play_x > 0
		&& vars->new_map[vars->play_y][vars->play_x - 1] != '1')
		move_player(vars, keycode);
	else if (keycode == KEY_S && vars->play_y < vars->map_y
		&& vars->new_map[vars->play_y + 1][vars->play_x] != '1')
		move_player(vars, keycode);
	else if (keycode == KEY_D && vars->play_x < vars->map_x
		&& vars->new_map[vars->play_y][vars->play_x + 1] != '1')
		move_player(vars, keycode);
	ft_putnbr_fd(vars->play_mov_cnt, 1);
	write(1, "\n", 1);
	return (0);
}
