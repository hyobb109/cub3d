/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:20:46 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/29 15:50:51 by hyobicho         ###   ########.fr       */
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

void	init_texture(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		vars->texture[i].id = 0;
		vars->texture[i].file_name = 0;
		vars->texture[i].img_height = 0;
		vars->texture[i].img_width = 0;
	}
}

void	init_vars(t_vars *vars, char *map_name)
{	
	vars->invalid_path_deque = malloc_deque(); // x
	vars->floor = -1;
	vars->ceiling = -1;
	vars->check_result = 0; // x
	vars->new_map = NULL;
	vars->map_x = -1;
	vars->map_y = -1;
	vars->play_coll_cnt = 0; // x
	vars->coll_cnt = 0; // x
	vars->exit_cnt = 0;
	vars->play_pos = 0;
	vars->play_mov_cnt = 0; // x
	vars->fd = open(map_name, O_RDONLY);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		print_error_exit(0);
	init_texture(vars);
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
		if (vars->ceiling != -1)
			print_error_exit("ceiling color already exists");
		vars->ceiling = ft_rgb_atoi(tmp[1]) * 256 * 256 + ft_rgb_atoi(tmp[2]) * 256 + ft_rgb_atoi(tmp[3]);
		if (vars->ceiling == vars->floor)
			print_error_exit("The floor and ceiling colors must be different");
	}
	else if (!ft_strncmp(tmp[0], "F", 2))
	{
		if (vars->floor != -1)
			print_error_exit("floor color already exists");
		vars->floor = ft_rgb_atoi(tmp[1]) * 256 * 256 + ft_rgb_atoi(tmp[2]) * 256 + ft_rgb_atoi(tmp[3]);
		if (vars->ceiling == vars->floor)
			print_error_exit("The floor and ceiling colors must be different");
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
		else if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			print_error_exit("Invalid map character");
		else
		{
			if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			{
				if (vars->play_pos)
					print_error_exit("We need only one player");	
				vars->play_pos = str[i];
			}
			dst[i] = str[i];
			no_blank++;
		}
	}
	dst[i] = '\0';
	if (!no_blank)
		print_error_exit("Map is empty");
	return (dst);
}

t_map	*init_map_node(char *str, int h, t_vars *vars)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		print_error_exit("malloc error");
	new->height = h + 1;
	new->str = check_blank(str, vars);
	new->width = ft_strlen(new->str);
	new->next = 0;
	return (new);
}

void print_maplst(t_map *map)
{
	t_map *tmp;

	tmp = map;
	while (tmp)
	{
		// printf("height: %d, width: %d, str: %s\n", tmp->height, tmp->width, tmp->str);
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
	print_maplst(map);
	printf("map_x: %d, map_y: %d\n", vars->map_x, vars->map_y);
	init_map(vars, map);
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