/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:03:42 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 20:27:14 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_deque	*malloc_deque(void)
{
	t_deque	*deque;

	deque = (t_deque *)malloc(sizeof(t_deque));
	if (deque)
		init_deque(deque);
	return (deque);
}

void	init_deque(t_deque *deque)
{
	deque->head = NULL;
	deque->tail = NULL;
	deque->len = 0;
}

void	init_element(t_elem *element, int x, int y)
{
	element->x = x;
	element->y = y;
	element->prev = NULL;
	element->next = NULL;
}

void	free_deque(t_deque *deque)
{
	t_elem	*popped;

	popped = NULL;
	while (deque->len)
	{
		popped = pop_back(deque);
		free(popped);
	}
	free(deque);
}
