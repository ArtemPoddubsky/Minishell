/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:04:31 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:04:32 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_l;
	size_t	src_l;

	dst_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	if (dst_l >= dstsize)
		return (dstsize + src_l);
	if (dstsize - dst_l <= src_l)
	{
		ft_memcpy(dst + dst_l, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	else
	{
		ft_memcpy(dst + dst_l, src, src_l + 1);
	}
	return (dst_l + src_l);
}
