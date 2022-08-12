/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:37:10 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:37:11 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pair	**sort_list(t_pair **env)
{
	char	*temp;
	t_pair	*first;
	t_pair	*util;

	first = *env;
	while (*env)
	{
		util = first;
		while (util)
		{
			if (ft_strcmp((*env)->key, util->key) < 0)
			{
				temp = (*env)->key;
				(*env)->key = util->key;
				util->key = temp;
				temp = (*env)->value;
				(*env)->value = util->value;
				util->value = temp;
			}
			util = util->next;
		}
		*env = (*env)->next;
	}
	*env = first;
	return (env);
}

int	print_export(t_pair *env)
{
	if (!env)
		return (1);
	sort_list(&env);
	while (env)
	{
		write(1, "declare -x ", 11);
		write(1, env->key, ft_strlen(env->key));
		write(1, "=\"", 2);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\"\n", 2);
		env = env->next;
	}
	return (0);
}
