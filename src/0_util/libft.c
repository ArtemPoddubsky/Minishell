/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:27 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:28 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_is_digits(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			i++;
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_mas(char **mas)
{
	int	i;

	if (mas)
	{
		i = 0;
		while (mas[i])
		{
			free(mas[i]);
			i++;
		}
		free(mas);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	char	*res;
	int		c;
	char	*s1_init;

	if (!s1 || !s2 || len > ft_strlen(s2))
		return (0);
	res = malloc((ft_strlen(s1) + len) + 1);
	if (!res)
		return (0);
	c = 0;
	s1_init = s1;
	while (*s1)
		res[c++] = *s1++;
	while (len--)
		res[c++] = *s2++;
	res[c] = 0;
	free(s1_init);
	return (res);
}

char	*ft_strjoin_free_second(char *s1, char *s2)
{
	char	*res;
	int		c;
	char	*s2_init;

	if (!s1 || !s2)
		return (0);
	res = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!res)
		return (0);
	c = 0;
	s2_init = s2;
	while (*s1)
		res[c++] = *s1++;
	while (*s2)
		res[c++] = *s2++;
	res[c] = 0;
	free(s2_init);
	return (res);
}
