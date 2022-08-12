/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:04:19 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:04:20 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_split(char **split)
{
	while (*split)
		free(*split++);
	return (0);
}

static size_t	check_end(const char *s, char c)
{
	size_t	count;

	if (ft_strchr(s, c))
		count = ft_strchr(s, c) - s;
	else
		count = ft_strlen(s);
	return (count);
}

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s && *s != c)
				s++;
			count++;
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;
	int		i;

	if (!s)
		return (0);
	words = count_words(s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (0);
	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		res[i] = ft_strndup(s, check_end(s, c));
		if (!res[i++])
			return (free_split(res));
		s = ft_strchr(s, c);
	}
	res[i] = 0;
	return (res);
}
