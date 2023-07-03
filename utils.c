/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:20:46 by yunjcho           #+#    #+#             */
/*   Updated: 2023/07/03 13:50:30 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(void)
{
	exit(0);
}

void	check_mapfile(t_vars *vars)
{
	int		cnt;
	char	*str;
	char	*trimmed;
	char	**tmp;

	cnt = 0;
	str = get_next_line(vars->fd);
	if (!str)
		print_error_exit("No return value from GNL");
	while (str)
	{
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
		if (cnt == 6)
			break ;
		str = get_next_line(vars->fd);
	}
	if (cnt != 6)
		print_error_exit("Element error");
	measure_map_size(vars);
}

char	*check_blank(const char *s, t_vars *vars)
{
	char	*dst;
	int		len;
	int		i;
	int		no_blank;
	char	*str;

	if (!s)
		return (0);
	str = ft_strtrim(s, "\n");
	len = ft_strlen(str);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == 0)
		print_error_exit("malloc error");
	i = -1;
	no_blank = 0;
	while (str[++i])
	{
		if (ft_isblank(str[i]))
			dst[i] = -1;
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
			dst[i] = str[i];
			no_blank++;
		}
	}
	free(str);
	dst[i] = '\0';
	if (!no_blank)
		print_error_exit("Map is empty");
	return (dst);
}

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
		free(str);
		free(trimmed);
		str = get_next_line(vars->fd);
		trimmed = ft_strtrim(str, " \v\r\f\n\t");
	}
	free(trimmed);
	map = 0;
	h = 0;
	map = init_map_node(str, h, vars);
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
	if (!vars->play_pos)
		print_error_exit("No player");
	init_map(vars, map);
}
