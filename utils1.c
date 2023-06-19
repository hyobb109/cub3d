/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:20:46 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/19 22:15:27 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(void)
{
	exit(1);
}

void	print_error_exit(char *err_msg)
{
	if (err_msg)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(err_msg, 2);
	}
	else
		ft_putendl_fd("Error", 2);
	exit(1);
}

void	init_vars(t_vars *vars, char *map_name)
{	
	vars->invalid_path_deque = malloc_deque(); // x
	vars->texture = NULL;
	vars->floor = NULL;
	vars->ceiling = NULL;
	vars->check_result = 0; // x
	vars->new_map = NULL;
	vars->map_x = -1;
	vars->map_y = -1;
	vars->play_coll_cnt = 0; // x
	vars->coll_cnt = 0; // x
	vars->exit_cnt = 0;
	vars->play_str_cnt = 0;
	vars->play_mov_cnt = 0; // x
	vars->fd = open(map_name, O_RDONLY);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		print_error_exit(0);
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
	{
		if (vars->ceiling)
			print_error_exit("ceiling color already exists");
		vars->ceiling = malloc(sizeof(t_color));
		if (!vars->ceiling)
			print_error_exit("malloc error");
		vars->ceiling->r = ft_rgb_atoi(tmp[1]);
		vars->ceiling->g = ft_rgb_atoi(tmp[2]);
		vars->ceiling->b = ft_rgb_atoi(tmp[3]);
		printf("type: %s r: %d, g: %d, b: %d\n", tmp[0], vars->ceiling->r, vars->ceiling->g, vars->ceiling->b);
	}
	else if (!ft_strncmp(tmp[0], "F", 2))
	{
		if (vars->floor)
			print_error_exit("floor color already exists");
		vars->floor = malloc(sizeof(t_color));
		if (!vars->floor)
			print_error_exit("malloc error");
		vars->floor->r = ft_rgb_atoi(tmp[1]);
		vars->floor->g = ft_rgb_atoi(tmp[2]);
		vars->floor->b = ft_rgb_atoi(tmp[3]);
		printf("type: %s r: %d, g: %d, b: %d\n", tmp[0], vars->floor->r, vars->floor->g, vars->floor->b);
	}
	else
		print_error_exit("Color type error");
}

void	check_element(t_vars *vars)
{
	char	*str;
	char	*trimmed;
	char	**tmp;
	int		cnt;

	cnt = 0;
	str = get_next_line(vars->fd);
	if (!str)
		print_error_exit("No return value from GNL");
	// 첫글자가 개행이면 다음 줄 받음
	// NO, SO, WE, EA, F, C 순서 없이 받음
	while (str)
	{
		trimmed = ft_strtrim(str, " \v\r\f\n\t");
		// printf("trimmed: %s\n", trimmed);
		free(str);
		if (trimmed[0] == 'F' || trimmed[0] == 'C')
		{
			tmp = ft_split2(trimmed, " \v\r\f\n\t,");
			// print_strs(tmp);
			save_color(vars, tmp);
			cnt++;
			printf("===color %d ===\n", cnt);
		}
		// element 저장 -> 
		else
		{
			tmp = ft_split2(trimmed, " \v\r\f\n\t");
			if (tmp[0])
			{
				// print_strs(tmp);
				save_element(vars, tmp);
				cnt++;
				printf("===texture %d ===\n", cnt);
			}
		}
		free_matrix(tmp);
		free(trimmed);
		if (cnt == 6)
			break ;
		str = get_next_line(vars->fd);
	}
	if (cnt != 6)
		print_error_exit("Element error");
	print_textures(vars->texture);
}

t_map	*init_map_node(char *str, int h)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		print_error_exit("malloc error");
	new->height = h;
	new->str = ft_strdup(str);
	new->width = ft_strlen(str) - 1;
	new->next = 0;
	return (new);
}

void print_maplst(t_map *map)
{
	t_map *tmp;

	tmp = map;
	while (tmp)
	{
		printf("height: %d, width: %d, str: %s\n", tmp->height, tmp->width, tmp->str);
		tmp = tmp->next;
	}
}
// libft error exit 으로 바꾸기 체크~!!!!
void	measure_map_size(t_vars *vars)
{
	char	*str;
	char	*trimmed;
	int		h;
	t_map	*map;
	t_map	*tmp;

	str = get_next_line(vars->fd);
	trimmed = ft_strtrim(str, " \v\r\f\n\t");
	while (str && !trimmed[0])
	{
		// printf("str: %s, ***trimmed: %s\n", str, trimmed);
		free(str);
		free(trimmed);
		str = get_next_line(vars->fd);
		trimmed = ft_strtrim(str, " \v\r\f\n\t");
	}
	free(trimmed);
	map = 0;
	h = 0;
	map = init_map_node(str, h);
	vars->map_x = map->width;
	tmp = map;
	while (str)
	{
		free(str);
		str = get_next_line(vars->fd);
		if (!str)
			break ;
		tmp->next = init_map_node(str, ++h);
		tmp = tmp->next;
		if (tmp->width > vars->map_x)
			vars->map_x = tmp->width;
	}
	close(vars->fd);
	vars->map_y = h;
	print_maplst(map);
	printf("map_x: %d, map_y: %d\n", vars->map_x, vars->map_y);
}

void print_strs(char **strs)
{
	int i;

	i = 0;
	if (!strs)
	{
		printf("null\n");
		return ;
	}
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}