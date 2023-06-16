/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:09:36 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 20:55:09 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*arr;
	size_t			i;
	unsigned int	s_len;

	i = 0;
	if (!s)
		return ((char *)ft_calloc(1, sizeof(char)));
	s_len = ft_strlen(s);
	if (start > s_len)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > s_len || len > s_len - start)
		len = s_len - start;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == 0)
		return (0);
	while (*s && i < len)
	{
		arr[i] = ((char *)s)[start];
		i++;
		start++;
	}
	arr[i] = '\0';
	return (arr);
}
