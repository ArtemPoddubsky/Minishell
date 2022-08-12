/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:46:57 by lholdo            #+#    #+#             */
/*   Updated: 2022/07/04 20:31:21 by Artem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len(t_pair *env)
{
	int	len;

	len = 0;
	while (env)
	{
		env = env->next;
		len++;
	}
	return (len);
}

char	**convert_to_double(t_pair *env)
{
	char	**new;
	char	*tmp;
	int		i;
	int		len;

	len = get_len(env);
	new = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(ft_strjoin(env->key, "="), env->value);
		if (!tmp)
			return (NULL);
		new[i] = ft_strdup(tmp);
		if (!new[i])
			return (NULL);
		free(tmp);
		env = env->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}
