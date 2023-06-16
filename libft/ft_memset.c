/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:37:40 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 16:05:29 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;
	unsigned char	chr;

	tmp = (unsigned char *)b;
	chr = (unsigned char)c;
	while (len--)
	{
		*tmp++ = chr;
	}
	return (b);
}
