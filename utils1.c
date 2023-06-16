/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:20:46 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/16 21:51:10 by hyobicho         ###   ########.fr       */
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
	vars->map_x = 1;
	vars->map_y = 1;
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

void	save_color(t_vars *vars, char *str)
{
	char	**tmp;
	int		cnt;

	printf("str: %s\n", str);
	tmp = ft_split2(str, " \v\r\f\n\t,");
	cnt = 0;
	while (tmp[cnt])
		cnt++;
	if (cnt != 4)
		print_error_exit("Color error");
	if (!ft_strncmp(tmp[0], "C", 2))
	{
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
		free(str);
		if (trimmed[0] == 'F' || trimmed[0] == 'C')
		{
			save_color(vars, trimmed);
			cnt++;
		}
		// element 저장 -> 
		else
		{
			tmp = ft_split2(trimmed, " \v\r\f\n\t");
			// save_element(vars, tmp);
			for (int k = 0; tmp[k]; k++) {
				printf("tmp[%d]: %s\n", k, tmp[k]);
			}
			free_matrix(tmp);
			if (trimmed[0])
				cnt++;
		}
		free(trimmed);
		printf("=== %d ===\n", cnt);
		if (cnt == 6)
			break ;
		str = get_next_line(vars->fd);
	}
}

void	measure_map_size(t_vars *vars)
{
	char	*str;
	char	*trimed;

	str = get_next_line(vars->fd);
	if (!str)
		print_error_exit("No return value from GNL");
	trimed = ft_strtrim(str, "\n");
	vars->map_x = ft_strlen(trimed);
	free(trimed);
	while (str)
	{
		free(str);
		str = get_next_line(vars->fd);
		if (str)
			vars->map_y++;
	}
	close(vars->fd);
}
