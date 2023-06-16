/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:07:23 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 16:20:22 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_invalid_path(t_vars *vars)
{
	t_elem	*popped;

	if (!vars->invalid_path_deque)
	{
		vars->err_msg = "No valid path found";
		return (0);
	}
	while (1)
	{
		vars->check_result = 0;
		vars->from_elem = vars->invalid_path_deque->head;
		if (!vars->from_elem->next)
			break ;
		vars->to_elem = vars->from_elem->next;
		if (!validate_path(vars))
		{
			vars->err_msg = "No valid path found";
			return (0);
		}
		popped = pop_front(vars->invalid_path_deque);
		free(popped);
	}
	return (1);
}

int	validate_path(t_vars *vars)
{
	t_deque		*check_queue;
	t_elem		*cur_elem;
	char		**check_array;

	check_queue = malloc_deque();
	check_array = make_visit_array(vars);
	append_back(check_queue, vars->from_elem->x, vars->from_elem->y);
	vars->cur_x = 0;
	vars->cur_y = 0;
	while (check_queue->len)
	{
		cur_elem = pop_front(check_queue);
		if (bfs_detail(vars, cur_elem, check_queue, check_array))
			break ;
		free(cur_elem);
		cur_elem = 0;
	}
	if (cur_elem)
		free(cur_elem);
	free_deque(check_queue);
	free_matrix(check_array);
	return (vars->check_result);
}

int	bfs_detail(t_vars *vars, t_elem *cur_elem,
	t_deque *check_queue, char **check_array)
{
	int			i;
	const int	dy[4] = {-1, 1, 0, 0};
	const int	dx[4] = {0, 0, -1, 1};

	i = 0;
	while (i < 4)
	{
		vars->cur_x = cur_elem->x + dx[i];
		vars->cur_y = cur_elem->y + dy[i];
		if (!is_continued(vars) && is_stuff(vars)
			&& check_array[vars->cur_y][vars->cur_x] == 'F')
		{
			if (vars->cur_x == vars->to_elem->x
				&& vars->cur_y == vars->to_elem->y)
			{
				vars->check_result = 1;
				break ;
			}
			append_back(check_queue, vars->cur_x, vars->cur_y);
			check_array[vars->cur_y][vars->cur_x] = 'T';
		}
		i++;
	}
	return (vars->check_result);
}

char	**make_visit_array(t_vars *vars)
{
	int		i;
	int		j;
	char	**check_array;

	j = 0;
	check_array = (char **)malloc(sizeof(char *) * (vars->map_y + 1));
	while (j < vars->map_y)
	{
		check_array[j] = (char *)malloc(sizeof(char) * vars->map_x + 1);
		i = 0;
		while (i < vars->map_x)
		{
			check_array[j][i] = 'F';
			i++;
		}
		check_array[j][i] = '\0';
		j++;
	}
	check_array[j] = 0;
	return (check_array);
}
