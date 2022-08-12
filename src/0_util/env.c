/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:34:42 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:34:43 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_pairs(t_pair *head)
{
	t_pair	*util;

	while (head)
	{
		util = head;
		free(head->key);
		free(head->value);
		head = head->next;
		free(util);
	}
}

int	add_env(t_pair **env, char *key, char *value)
{
	t_pair	*pair;
	t_pair	*util;

	pair = malloc(sizeof(t_pair));
	if (!pair)
		return (0);
	pair->key = ft_strdup(key);
	if (!value)
		pair->value = ft_strdup("");
	else
		pair->value = ft_strdup(value);
	pair->next = NULL;
	if (!*env)
		*env = pair;
	else
	{
		util = *env;
		while (util->next)
			util = util->next;
		util->next = pair;
		pair->previous = util;
	}
	return (1);
}

void	free_splitted_env(char **tmp)
{
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
}

char	**split_env(char *env)
{
	char	**str;
	char	*eq;

	if (!env)
		return (NULL);
	str = malloc(sizeof(char *) * 3);
	if (!str)
		return (NULL);
	eq = ft_strchr(env, '=');
	if (*(eq + 1) == '\0')
	{
		str[0] = ft_strndup(env, ft_strlen(env) - 1);
		str[1] = NULL;
		str[2] = NULL;
	}
	else
	{
		str[0] = ft_strndup(env, ft_strlen(env) - ft_strlen(eq));
		str[1] = ft_strndup(eq + 1, ft_strlen(eq) - 1);
		str[2] = NULL;
	}
	return (str);
}

t_pair	*get_env_value(t_pair *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}
