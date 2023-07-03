/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:20:46 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 16:24:04 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(void)
{
	exit(0);
}

static int	count_data(t_vars *vars, char *str, int cnt)
{
	char	*trimmed;
	char	**tmp;

	trimmed = ft_strtrim(str, " \v\r\f\n\t");
	free(str);
	if (trimmed[0] == 'F' || trimmed[0] == 'C')
	{
		tmp = ft_split2(trimmed, " \v\r\f\n\t,");
		save_color(vars, tmp);
		cnt++;
	}
	else
	{
		tmp = ft_split2(trimmed, " \v\r\f\n\t");
		if (tmp[0])
		{
			save_element(vars, tmp);
			cnt++;
		}
	}
	free_matrix(tmp);
	free(trimmed);
	return (cnt);
}

// 파일 분리하기
static void	check_blank(char *dst, char *str, int *no_blank, t_vars *vars)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (ft_isblank(str[i]))
			*dst = -1;
		else if (str[i] != '1' && str[i] != '0' && str[i] != 'N' \
		&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			print_error_exit("Invalid map character");
		else
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' \
			|| str[i] == 'W')
			{
				if (vars->play_pos)
					print_error_exit("We need only one player");
				vars->play_pos = str[i];
			}
			*dst = str[i];
			(*no_blank)++;
		}
		dst++;
	}
	*dst = '\0';
}

static char	*copy_str(const char *s, t_vars *vars)
{
	char	*dst;
	int		no_blank;
	char	*str;

	if (!s)
		return (0);
	str = ft_strtrim(s, "\n");
	dst = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (dst == 0)
		print_error_exit("malloc error");
	no_blank = 0;
	check_blank(dst, str, &no_blank, vars);
	free(str);
	if (!no_blank)
		print_error_exit("Map is empty");
	return (dst);
}

static t_map	*init_map_node(char *str, int h, t_vars *vars)
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

void	measure_map_size(t_vars *vars, t_map *map, char	*str)
{
	int		h;
	t_map	*tmp;

	h = 0;
	vars->map_x = map->width;
	tmp = map;
	while (str)
	{
		free(str);
		str = get_next_line(vars->fd);
		if (!str)
			break ;
		tmp->next = init_map_node(str, ++h, vars);
		tmp = tmp->next;
		if (tmp->width > vars->map_x)
			vars->map_x = tmp->width;
	}
	close(vars->fd);
	vars->map_y = h + 1;
	if (!map->str)
		print_error_exit("No map");
	if (!vars->play_pos)
		print_error_exit("No player");
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

void	check_mapfile(t_vars *vars)
{
	int		cnt;
	char	*str;
	t_map	*map;

	cnt = 0;
	map = 0;
	str = get_next_line(vars->fd);
	if (!str)
		print_error_exit("No return value from GNL");
	while (str)
	{
		cnt = count_data(vars, str, cnt);
		if (cnt == 6)
			break ;
		str = get_next_line(vars->fd);
	}
	if (cnt != 6)
		print_error_exit("Element error");
	str = init_map_head(vars, &map);
	measure_map_size(vars, map, str);
	init_map(vars, map);
}
