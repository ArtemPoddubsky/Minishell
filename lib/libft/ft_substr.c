/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:04:51 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:04:52 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	len_s;
	size_t	j;

	if (!s)
		return (0);
	i = start;
	j = 0;
	len_s = ft_strlen(s);
	while (i < len_s && s[i++])
		j++;
	if (j > len)
		j = len;
	res = malloc(j + 1);
	if (!res)
		return (0);
	len = 0;
	while (j-- && s[start])
		res[len++] = s[start++];
	res[len] = 0;
	return (res);
}
