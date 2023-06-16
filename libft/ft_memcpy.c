/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:27:22 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/15 13:34:44 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*tmp;
	unsigned const char	*tmp2;

	if (!dst && !src)
		return (0);
	tmp = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	while (n)
	{
		*tmp++ = *tmp2++;
		n--;
	}
	return (dst);
}
