/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:12:21 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 18:42:08 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*arr;

	i = 0;
	if (!s || !f)
		return (0);
	len = ft_strlen(s);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == 0)
		return (0);
	while (*s && i < len)
	{
		arr[i] = f(i, s[i]);
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
