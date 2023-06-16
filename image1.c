/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:20:57 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 21:39:57 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_images(t_texture **head, t_vars *vars)
{
	int			idx;
	const char	image_code[7] = {NO, SO, WE, EA, FLOOR, CEILING, 0};

	idx = 0;
	while (image_code[idx])
	{
		find_image_node(head, vars, image_code[idx]);
		if (!head)
			print_error_exit(0);
		idx++;
	}
}

t_texture	*find_image_node(t_texture **head, t_vars *vars, char image_code)
{
	t_texture	*lst;

	lst = *head;
	while (lst)
	{
		if (lst->code == image_code)
			return (lst);
		lst = lst->next;
	}
	return (image_lstadd_back(head, vars, image_code));
}

t_texture	*image_lstadd_back(t_texture **head, t_vars *vars, char image_code)
{
	t_texture	*new_node;
	t_texture	*lst;
	char	*file_name;

	new_node = malloc(sizeof(t_texture));
	file_name = get_image_file_name(new_node, image_code);
	if (new_node && file_name)
	{
		init_image_node(new_node, vars, image_code);
		lst = *head;
		if (lst)
		{
			while (lst->next)
				lst = lst->next;
			lst->next = new_node;
			new_node->prev = lst;
		}
		else
		{
			*head = new_node;
			new_node->prev = 0;
		}
	}
	return (new_node);
}

char	*get_image_file_name(t_texture	*new_node, char image_code)
{
	new_node->file_name = NULL;
	if (image_code == 'B')
		new_node->file_name = "./img/wall_N.xpm";
	else if (image_code == 'E')
		new_node->file_name = "./img/wall_E.xpm";
	else if (image_code == 'P')
		new_node->file_name = "./img/wall_S.xpm";
	else if (image_code == '1')
		new_node->file_name = "./img/wall_W.xpm";
	// else if (image_code == 'C')
	// 	new_node->file_name = "./img/collection.xpm";
	return (new_node->file_name);
}

t_texture	*init_image_node(t_texture *new_node, t_vars *vars, char image_code)
{
	new_node->code = image_code;
	new_node->img_height = 0;
	new_node->img_width = 0;
	new_node->prev = 0;
	new_node->next = 0;
	new_node->img = NULL;
	if (image_code != 'D')
	{
		new_node->img = mlx_xpm_file_to_image(vars->mlx, \
			new_node->file_name, &new_node->img_width, &new_node->img_height);
	}
	return (new_node);
}
