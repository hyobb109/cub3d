/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:15:13 by hyobicho          #+#    #+#             */
/*   Updated: 2023/06/21 14:46:05 by hyobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	incharset(char a, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (a == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static unsigned int	ft_strlen1(char *s, char *charset)
{
	int	i;

	i = 0;
	while (s[i] && (!(incharset(s[i], charset))))
		i++;
	return (i);
}

static char	**result(char **res, char *str, char *charset, int cnt)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < cnt)
	{
		len = ft_strlen1(str, charset);
		res[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (res[i] == NULL)
			print_error_exit(0);
		j = 0;
		while (j < len)
		{
			res[i][j] = str[j];
			j++;
		}
		res[i][j] = '\0';
		while (incharset(str[j], charset) && str[j])
			j++;
		str += j;
		i++;
	}
	res[i] = 0;
	return (res);
}

static unsigned int	cntstr(char *s, char *charset)
{
	int	cnt;
	int	i;
	int	flag;

	cnt = 0;
	i = 0;
	flag = 1;
	while (s[i])
	{
		if (!incharset(s[i], charset) && flag)
		{
			cnt++;
			flag = 0;
		}
		else if (incharset(s[i], charset))
			flag = 1;
		i++;
	}
	return (cnt);
}

char	**ft_split2(char *str, char *charset)
{
	char			**res;
	unsigned int	cnt;

	if (!str)
		return (0);
	while (incharset(*str, charset))
		str++;
	cnt = cntstr(str, charset);
	res = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (res == NULL)
		print_error_exit("malloc error");
	return (result(res, str, charset, cnt));
}
