/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:10:10 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 18:40:30 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (arr == 0)
		return (0);
	while (*s1)
	{
		*arr++ = *(char *)s1++;
	}
	while (*s2)
	{
		*arr++ = *(char *)s2++;
	}
	*arr = '\0';
	return (arr - (s1_len + s2_len));
}
