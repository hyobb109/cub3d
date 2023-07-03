/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:20:57 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 21:44:54 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_filename(t_vars *vars, char *file_name)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (vars->texture[i].file_name)
		{
			if (!ft_strncmp(vars->texture[i].file_name, file_name, \
				ft_strlen(file_name) + 1))
				print_error_exit("Texture file name cannot be duplicated");
		}
	}
}

static void	init_texture_info(t_vars *vars, char **texture, int texture_id)
{
	check_filename(vars, texture[1]);
	if (vars->texture[texture_id].file_name)
		print_error_exit("Texture identifier cannot be duplicated");
	vars->texture[texture_id].file_name = ft_strdup(texture[1]);
	vars->texture[texture_id].img.ptr = mlx_xpm_file_to_image(vars->mlx, \
		vars->texture[texture_id].file_name, \
		&vars->texture[texture_id].img_width, \
		&vars->texture[texture_id].img_height);
	if (!vars->texture[texture_id].img.ptr)
		print_error_exit("Texture file does not exist");
}

void	save_element(t_vars *vars, char **texture)
{
	int	cnt;

	cnt = 0;
	while (texture[cnt])
		cnt++;
	if (cnt != 2)
		print_error_exit("Texture Format error");
	if (!ft_strncmp(texture[0], "NO", 3))
		init_texture_info(vars, texture, NO);
	else if (!ft_strncmp(texture[0], "SO", 3))
		init_texture_info(vars, texture, SO);
	else if (!ft_strncmp(texture[0], "WE", 3))
		init_texture_info(vars, texture, WE);
	else if (!ft_strncmp(texture[0], "EA", 3))
		init_texture_info(vars, texture, EA);
	else
		print_error_exit("Invalid Texture Id");
}

static void	init_color(int *color1, int color2, char **tmp)
{
	if (*color1 != -1)
		print_error_exit("Color already exists");
	*color1 = ft_rgb_atoi(tmp[1]) * 256 * 256 + ft_rgb_atoi(tmp[2]) * 256 \
	+ ft_rgb_atoi(tmp[3]);
	if (*color1 == color2)
		print_error_exit("The floor and ceiling colors must be different");
}

void	save_color(t_vars *vars, char **tmp)
{
	int		cnt;

	cnt = 0;
	while (tmp[cnt])
		cnt++;
	if (cnt != 4)
		print_error_exit("Color error");
	if (!ft_strncmp(tmp[0], "C", 2))
		init_color(&vars->ceiling, vars->floor, tmp);
	else if (!ft_strncmp(tmp[0], "F", 2))
		init_color(&vars->floor, vars->ceiling, tmp);
	else
		print_error_exit("Color type error");
}
