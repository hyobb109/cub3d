/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:58:54 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 16:07:27 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	append_front(t_deque *deque, int x, int y)
{
	t_elem	*new_element;

	new_element = (t_elem *)malloc(sizeof(t_elem));
	if (!new_element)
		return ;
	init_element(new_element, x, y);
	if (!deque->head)
	{
		deque->head = new_element;
		deque->tail = new_element;
	}
	else
	{
		deque->head->prev = new_element;
		new_element->next = deque->head;
		deque->head = new_element;
	}
	deque->len++;
}

void	append_back(t_deque *deque, int x, int y)
{
	t_elem	*new_element;

	new_element = (t_elem *)malloc(sizeof(t_elem));
	if (!new_element)
		return ;
	init_element(new_element, x, y);
	if (!deque->tail)
	{
		deque->head = new_element;
		deque->tail = new_element;
	}
	else
	{
		new_element->prev = deque->tail;
		deque->tail->next = new_element;
		deque->tail = new_element;
	}
	deque->len++;
}

t_elem	*pop_front(t_deque *deque)
{
	t_elem	*tmp;

	if (deque->len)
	{
		tmp = deque->head;
		deque->head = tmp->next;
		if (deque->head)
			deque->head->prev = 0;
		tmp->next = 0;
		deque->len--;
		if (deque->len == 0)
		{
			deque->head = 0;
			deque->tail = 0;
		}
		return (tmp);
	}
	return (0);
}

t_elem	*pop_back(t_deque *deque)
{
	t_elem	*tmp;

	if (deque->len)
	{
		tmp = deque->tail;
		deque->tail = tmp->prev;
		if (deque->tail)
			deque->tail->next = 0;
		tmp->prev = 0;
		deque->len--;
		if (deque->len == 0)
		{
			deque->head = 0;
			deque->tail = 0;
		}
		return (tmp);
	}
	return (0);
}
