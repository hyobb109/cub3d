/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:04:01 by yunjcho           #+#    #+#             */
/*   Updated: 2023/06/21 14:46:38 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*arr;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == 0)
		print_error_exit("malloc error");
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
