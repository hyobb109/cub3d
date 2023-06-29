/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:20:57 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/29 15:59:58 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	init_texture_info(t_vars *vars, char **texture, int texture_id)
{
	vars->texture[texture_id].id = ft_strdup(texture[0]);
	if (vars->texture[texture_id].file_name)
		print_error_exit("This texture identifier already exists");
	vars->texture[texture_id].file_name = ft_strdup(texture[1]);
	vars->texture[texture_id].img.ptr = mlx_xpm_file_to_image(vars->mlx, \
		vars->texture[texture_id].file_name, &vars->texture[texture_id].img_width, &vars->texture[texture_id].img_height);
}

void	save_element(t_vars *vars, char **texture)
{
	int	cnt;

	cnt = 0;
	while (texture[cnt])
	{
		// printf("s: %s, cnt: %d\n", texture[cnt], cnt);
		cnt++;
	}
	if (cnt != 2)
		print_error_exit("Texture Format error");
	if (!ft_strncmp(texture[0], "NO", 3))
	{
		init_texture_info(vars, texture, NO);
	}
	else if (!ft_strncmp(texture[0], "SO", 3))
	{
		init_texture_info(vars, texture, SO);
	}
	else if (!ft_strncmp(texture[0], "WE", 3))
	{
		init_texture_info(vars, texture, WE);
	}
	else if (!ft_strncmp(texture[0], "EA", 3))
	{
		init_texture_info(vars, texture, EA);
	}
	else
		print_error_exit("Invalid Texture Id");
}

// void	make_texture_matrix(t_texture *new_node)
// {
// 	int		idx;

// 	new_node->colors = malloc(sizeof(char *) * (new_node->img_height + 1));
// 	if (!new_node->colors)
// 		print_error_exit("Malloc Error");
// 	idx = -1;
// 	while (++idx < new_node->img_height + 1)
// 	{
// 		new_node->colors[idx] = malloc(sizeof(char) * (new_node->img_width + 1));
// 		if (!new_node->colors[idx])
// 			print_error_exit("Malloc Error");
// 		new_node->colors[idx] = mlx_get_data_addr(new_node->img->ptr, &new_node->img->bpp, &new_node->img->len, &new_node->img->endian);
// 		printf("new_node->filename : %s\n", new_node->file_name);
// 		printf("new_node->colors[%d]: %s, len : %d\n", idx, new_node->colors[idx], new_node->img_width);
// 	}
// 	new_node->colors[idx] = 0;
// }


void	print_textures(t_texture *texture)
{
	for (int i = 0; i < 4; i++)
	{
		printf("texture[%d].id : %s\n", i, texture[i].id);
		printf("texture[%d].file_name : %s\n", i, texture[i].file_name);
		printf("texture[%d].img_width : %d\n", i, texture[i].img_width);
		printf("texture[%d].img_height : %d\n", i, texture[i].img_height);
	}
}