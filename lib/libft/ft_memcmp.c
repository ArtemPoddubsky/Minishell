/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:03:58 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:03:59 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*ch;
	unsigned const char	*cch;

	ch = s1;
	cch = s2;
	while (n--)
	{
		if (*ch != *cch)
			return (*ch - *cch);
		ch++;
		cch++;
	}
	return (0);
}
