/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:04:49 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:04:50 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contains(char cat, char const *cats)
{
	while (*cats)
	{
		if (*cats++ == cat)
			return (1);
	}
	return (0);
}

static int	get_len(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && contains(s1[start], set))
	{
		i++;
		start++;
	}
	if (start - 1 == end)
		return (0);
	while (s1[end] && contains(s1[end], set))
	{
		i++;
		end--;
	}
	return (ft_strlen(s1) - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;

	if (!s1)
		return (0);
	i = 0;
	j = get_len(s1, set);
	res = malloc(j + 1);
	if (!res)
		return (0);
	while (*s1 && contains(*s1, set))
		s1++;
	while (*s1 && j--)
		res[i++] = *s1++;
	res[i] = 0;
	return (res);
}
