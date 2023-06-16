/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunjcho <yunjcho@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:25:57 by yunjcho           #+#    #+#             */
/*   Updated: 2022/07/23 16:54:22 by yunjcho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_digit(long long nbr)
{
	int	dig;

	dig = 0;
	if (nbr <= 0)
	{
		dig++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		dig++;
		nbr /= 10;
	}
	return (dig);
}

static int	ft_make_divisor(int dig, long long nbr)
{
	int	div;
	int	digit;

	div = 1;
	digit = dig - 1;
	if (nbr < 0)
	{	
		digit--;
		nbr *= -1;
	}
	if (nbr >= 0 && nbr <= 9)
		return (div);
	while (digit)
	{
		div *= 10;
		digit--;
	}
	return (div);
}

static char	*ft_translate_itoa(int dig, int div, long long nbr, char *str)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		str[0] = '-';
		dig--;
		i++;
		nbr *= -1;
	}
	while (dig)
	{
		str[i] = nbr / div + '0';
		nbr %= div;
		div /= 10;
		i++;
		dig--;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int			dig;
	int			div;
	char		*str;
	long long	nbr;

	nbr = n;
	dig = ft_get_digit(nbr);
	str = (char *)malloc(sizeof(char) * dig + 1);
	if (str == 0)
		return (0);
	div = ft_make_divisor(dig, nbr);
	return (ft_translate_itoa(dig, div, nbr, str));
}
