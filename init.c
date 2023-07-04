/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:53:36 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/04 13:00:56 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		vars->texture[i].file_name = 0;
		vars->texture[i].img_height = 0;
		vars->texture[i].img_width = 0;
	}
}

void	init_vars(t_vars *vars, char *map_name)
{	
	vars->floor = -1;
	vars->ceiling = -1;
	vars->new_map = NULL;
	vars->map_x = -1;
	vars->map_y = -1;
	vars->play_pos = 0;
	vars->angle = 30 * PI / 180;
	vars->fd = open(map_name, O_RDONLY);
	if (vars->fd < 0)
		print_error_exit("open error");
	vars->mlx = mlx_init();
	if (!vars->mlx)
		print_error_exit(0);
	init_texture(vars);
}

t_map	*init_map_node(char *str, int h, t_vars *vars)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		print_error_exit("malloc error");
	new->height = h + 1;
	new->str = copy_str(str, vars);
	new->width = ft_strlen(new->str);
	new->next = 0;
	return (new);
}

char	*init_map_head(t_vars *vars, t_map **map)
{
	char	*str;
	char	*trimmed;

	str = get_next_line(vars->fd);
	trimmed = ft_strtrim(str, " \v\r\f\n\t");
	while (str && !trimmed[0])
	{
		free(str);
		free(trimmed);
		str = get_next_line(vars->fd);
		trimmed = ft_strtrim(str, " \v\r\f\n\t");
	}
	free(trimmed);
	*map = init_map_node(str, 0, vars);
	return (str);
}
