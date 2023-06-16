/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 04:50:31 by hyobicho          #+#    #+#             */
/*   Updated: 2023/06/16 21:40:16 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 수정할 것 -> 음수, 256 이상 프린트에러
int	ft_rgb_atoi(const char *str)
{
	long long	res;
	int			i;

	// while (ft_isblank(*str))
	// 	str++;
	if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	res = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res < 0 || res > 255 || str[i] != '\0')
		print_error_exit("Color range error");
	return (res);
}