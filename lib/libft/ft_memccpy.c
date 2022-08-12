/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:03:54 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:03:55 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*ch;
	unsigned const char	*cch;

	if (!dst && !src)
		return (dst);
	ch = dst;
	cch = src;
	while (n--)
	{
		*ch = *cch;
		if (*cch == (unsigned char)c)
			return (++ch);
		ch++;
		cch++;
	}
	return (0);
}
