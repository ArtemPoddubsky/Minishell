/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:03:28 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:05:26 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int	count;

	if (n < 0)
		count = 1;
	else
		count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	reverse(char *hey)
{
	char	*util;
	char	tmp;

	util = hey + ft_strlen(hey) - 1;
	if (*hey == '-')
		hey++;
	while (util > hey)
	{
		tmp = *util;
		*util-- = *hey;
		*hey++ = tmp;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*res;
	long	l_n;

	l_n = n;
	str = malloc(numlen(n) + 1);
	res = str;
	if (!str)
		return (0);
	if (n < 0)
	{
		*str++ = '-';
		l_n = -l_n;
	}
	if (l_n == 0)
		*str++ = '0';
	while (l_n != 0)
	{
		*str++ = l_n % 10 + '0';
		l_n /= 10;
	}
	*str = 0;
	reverse(res);
	return (res);
}
