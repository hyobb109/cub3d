/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:41:39 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/24 15:38:35 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur_node;
	t_list	*next_node;

	cur_node = *lst;
	while (cur_node)
	{
		next_node = cur_node->next;
		ft_lstdelone(cur_node, del);
		cur_node = next_node;
	}
	*lst = 0;
}
