/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:10:49 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 18:40:59 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_start_idx(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	set_len;

	i = -1;
	set_len = ft_strlen(set);
	while (s1[++i])
	{
		j = -1;
		while (set[++j])
		{
			if (s1[i] == set[j])
				break ;
		}
		if (j == set_len)
		{
			return (i);
		}
	}
	return (i);
}

static	int	get_end_idx(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	k;
	int	set_len;

	i = -1;
	set_len = ft_strlen(set);
	while (s1[++i])
	{
		j = -1;
		while (set[++j])
		{
			if (s1[i] == set[j])
				break ;
		}
		if (j == set_len)
		{
			k = i;
		}
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		n;
	char	*arr;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = get_start_idx(s1, set);
	end = get_end_idx(s1, set);
	n = 0;
	arr = (char *)malloc(sizeof(char) * (end - start + 2));
	if (arr == 0)
		return (0);
	while (start < end + 1)
	{
		arr[n] = s1[start];
		n++;
		start++;
	}
	arr[n] = '\0';
	return (arr);
}
