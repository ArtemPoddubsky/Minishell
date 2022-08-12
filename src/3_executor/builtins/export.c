/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:37:07 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:37:08 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pair	*find_alphabetic(t_pair *env, char *content)
{
	t_pair	*prev;
	t_pair	*walk;
	char	**tmp;

	prev = env;
	walk = env->next;
	tmp = ft_split(content, '=');
	if (!tmp)
		return (NULL);
	while (walk && ft_strncmp(walk->key, tmp[0], ft_strlen(tmp[0])) > 0)
	{
		prev = walk;
		walk = walk->next;
	}
	free_mas(tmp);
	return (prev);
}

int	contains_name(char *content, t_pair *env)
{
	char	**tmp;

	while (env)
	{
		tmp = ft_split(content, '=');
		if (!ft_strncmp(tmp[0], env->key, ft_strlen(tmp[0])))
		{
			ft_strlcpy(env->value, tmp[1], ft_strlen(tmp[1]) + 1);
			free_mas(tmp);
			return (1);
		}
		free_mas(tmp);
		env = env->next;
	}
	return (0);
}

t_pair	*add_var(char *content)
{
	t_pair	*tmp1;
	char	**tmp;

	tmp1 = ft_calloc(1, sizeof(t_pair));
	if (!tmp1)
		return (NULL);
	tmp = ft_split(content, '=');
	if (!tmp)
		return (NULL);
	tmp1->key = ft_substr(tmp[0], 0, ft_strlen(tmp[0]));
	tmp1->value = ft_substr(tmp[1], 0, ft_strlen(tmp[1]));
	free_mas(tmp);
	return (tmp1);
}

static int	redirect_type(t_token *tokens)
{
	if (tokens->type == T_QUOTE || tokens->type == T_EMPTY
		|| tokens->type == T_BUILTIN
		|| tokens->type == T_COMMAND)
		return (0);
	return (1);
}

int	export(t_token *tokens, t_pair *env)
{
	t_pair	*first;
	t_pair	*tmp1;

	if (!tokens || redirect_type(tokens))
		return (print_export(env));
	first = env;
	while (tokens && (tokens->type == T_COMMAND
			|| tokens->type == T_QUOTE))
	{
		tokens->content = check_quotes(tokens);
		if (!contains_name(tokens->content, env))
		{
			env = first;
			first = find_alphabetic(first, tokens->content);
			while (env != first)
				env = env->next;
			env = first->next;
			tmp1 = add_var(tokens->content);
			tmp1->next = env;
			first->next = tmp1;
		}
		tokens = tokens->next;
	}
	return (0);
}
