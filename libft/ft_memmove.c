/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 19:39:07 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 21:34:39 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_for_ovlp(unsigned char *tmp,
		unsigned const char *tmp2, size_t len)
{
	int	idx;

	idx = len - 1;
	while (len--)
	{
		tmp[idx] = tmp2[idx];
		idx--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*tmp;
	unsigned const char		*tmp2;

	if (!dst && !src)
		return (0);
	tmp = (unsigned char *)dst;
	tmp2 = (unsigned char *)src;
	if (tmp > tmp2 && (tmp - tmp2) < (int) len)
	{
		ft_for_ovlp(tmp, tmp2, len);
		return (dst);
	}
	ft_memcpy(dst, src, (sizeof(*tmp2) * len));
	return (dst);
}
