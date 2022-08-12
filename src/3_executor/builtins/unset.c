/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:37:13 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:37:14 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_var(t_pair *env, t_pair *prev)
{
	free(env->key);
	free(env->value);
	prev->next = env->next;
	free(env);
	env = prev;
}

char	*check_quotes(t_token *tokens)
{
	int		i;
	int		count;
	char	*tmp;

	count = ft_strlen(tokens->content);
	if (!count)
		return ("");
	if ((tokens->content[0] == '"' || tokens->content[0] == '\'')
		&& (tokens->content[count - 1] == '"'
			|| tokens->content[count - 1] == '\''))
	{
		tmp = (char *)malloc(sizeof(char) * count - 2);
		if (!tmp)
			return (NULL);
		i = 0;
		while (i < count - 2)
		{
			tmp[i] = tokens->content[i + 1];
			i++;
		}
		tmp[i] = '\0';
		free(tokens->content);
		tokens->content = tmp;
	}
	return (tokens->content);
}

int	unset(t_token *tokens, t_pair *env)
{
	t_pair	*prev;
	t_pair	*head;

	head = env;
	while (tokens && (tokens->type == T_COMMAND || tokens->type == T_QUOTE))
	{
		env = head;
		prev = NULL;
		while (env)
		{
			tokens->content = check_quotes(tokens);
			if (!tokens->content)
				return (1);
			if (ft_strcmp(tokens->content, env->key))
				prev = env;
			else
			{
				unset_var(env, prev);
				break ;
			}
			env = env->next;
		}
		tokens = tokens->next;
	}
	return (0);
}
