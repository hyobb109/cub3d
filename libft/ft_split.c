/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:11:16 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 18:41:27 by yunjcho          ###   ########.fr       */
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
		return (0);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
	return (0);
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
		return (0);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			arr[i] = ft_insert_str(s, c);
			if (!arr[i])
				return (ft_free(arr));
			i++;
		}
		while (*s && (*s != c))
			s++;
	}
	arr[i] = 0;
	return (arr);
}
