/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:50:42 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 21:36:42 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_images(t_texture **head)
{
	t_texture	*lst;
	t_texture	*tmp;

	lst = *head;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}
