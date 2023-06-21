/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:11:16 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/21 14:48:45 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_size(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		if (s[i])
			cnt++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (cnt);
}

static	int	ft_split_strlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && (s[len] != c))
		len++;
	return (len);
}

static char	*ft_insert_str(char const *s, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_split_strlen(s, c);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		print_error_exit("malloc error");
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;

	if (!s)
		return (0);
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (get_size(s, c) + 1));
	if (arr == 0)
		print_error_exit("malloc error");
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			arr[i] = ft_insert_str(s, c);
			if (!arr[i])
				print_error_exit("malloc error");
			i++;
		}
		while (*s && (*s != c))
			s++;
	}
	arr[i] = 0;
	return (arr);
}
