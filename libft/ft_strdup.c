/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:04:01 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 16:45:34 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*arr;

	len = ft_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == 0)
		return (0);
	else
	{
		while (*s1)
		{
			*arr = *s1;
			arr++;
			s1++;
		}
		*arr = '\0';
	}
	return (arr - len);
}
