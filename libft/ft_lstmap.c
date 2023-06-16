/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:42:27 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 14:34:12 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*cur;

	if (!lst || !f)
		return (0);
	res = ft_lstnew(f(lst->content));
	if (!res)
		return (0);
	cur = res;
	lst = lst->next;
	while (lst)
	{
		cur->next = ft_lstnew(f(lst->content));
		if (!(cur->next))
		{
			ft_lstclear(&res, del);
			return (0);
		}
		cur = cur->next;
		lst = lst->next;
	}
	return (res);
}
