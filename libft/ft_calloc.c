/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:03:18 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/25 23:57:39 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (count >= SIZE_MAX / size)
		return (0);
	arr = (void *)malloc(count * size);
	if (arr == 0)
		return (0);
	ft_bzero(arr, (count * size));
	return (arr);
}
