/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:20:57 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/28 20:45:25 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_element(t_vars *vars, char **texture)
{
	t_texture	*lst;

	lst = vars->texture;
	while (lst)
	{
		if (!ft_strncmp(lst->id, texture[0], 3))
			print_error_exit("This texture identifier already exists");
		if (!ft_strncmp(lst->file_name, texture[1], ft_strlen(texture[1])))
			print_error_exit("This texture file already exists");
		lst = lst->next;
	}
	texture_lstadd_back(vars, texture);
}

t_texture	*texture_lstadd_back(t_vars *vars, char **texture)
{
	t_texture	*new_node;
	t_texture	*lst;

	new_node = malloc(sizeof(t_texture));
	if (!new_node)
		print_error_exit("Malloc Error");
	init_texture_node(new_node, vars, texture);
	lst = vars->texture;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new_node;
		new_node->prev = lst;
	}
	else
	{
		vars->texture = new_node;
		new_node->prev = 0;
	}
	return (new_node);
}

void	make_texture_matrix(t_texture *new_node)
{
	int		idx;

	new_node->colors = malloc(sizeof(char *) * (new_node->img_height + 1));
	if (!new_node->colors)
		print_error_exit("Malloc Error");
	idx = -1;
	while (++idx < new_node->img_height + 1)
	{
		new_node->colors[idx] = malloc(sizeof(char) * (new_node->img_width + 1));
		if (!new_node->colors[idx])
			print_error_exit("Malloc Error");
		new_node->colors[idx] = mlx_get_data_addr(new_node->img, &new_node->img->bpp, &new_node->img_width, &new_node->img->endian);
		printf("new_node->filename : %s\n", new_node->file_name);
		printf("new_node->colors[%d]: %s, len : %d\n", idx, new_node->colors[idx], new_node->img_width);
	}
	new_node->colors[idx] = 0;
}


t_texture	*init_texture_node(t_texture *new_node, t_vars *vars, char **texture)
{
	get_texture_file_name(new_node, texture);
	new_node->img_height = 0;
	new_node->img_width = 0;
	new_node->prev = 0;
	new_node->next = 0;
	new_node->img = mlx_xpm_file_to_image(vars->mlx, \
		new_node->file_name, &new_node->img_width, &new_node->img_height);
	if (!new_node->img)
		print_error_exit("Texture file path error");
	make_texture_matrix(new_node);
	return (new_node);
}

void	get_texture_file_name(t_texture *new_node, char **texture)
{
	int	cnt;

	new_node->file_name = NULL;
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
		new_node->id = "NO";
		new_node->file_name = ft_strdup(texture[1]);
	}
	else if (!ft_strncmp(texture[0], "SO", 3))
	{
		new_node->id = "SO";
		new_node->file_name = ft_strdup(texture[1]);
	}
	else if (!ft_strncmp(texture[0], "WE", 3))
	{
		new_node->id = "WE";
		new_node->file_name = ft_strdup(texture[1]);
	}
	else if (!ft_strncmp(texture[0], "EA", 3))
	{
		new_node->id = "EA";
		new_node->file_name = ft_strdup(texture[1]);
	}
	else
		print_error_exit("Invalid Texture Id");
}

void	print_textures(t_texture *head)
{
	t_texture *tmp;

	tmp = head;
	while (tmp)
	{
		printf("Id: %s, filepath : %s, width : %d, height : %d, prev : %p, next : %p\n", tmp->id, tmp->file_name, tmp->img_width, tmp->img_height, tmp->prev, tmp->next);
		tmp = tmp->next;
	}
}