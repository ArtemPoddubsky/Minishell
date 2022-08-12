/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:29 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:35 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	choose_token(t_token *token, char *cmd, int *i)
{
	if (ft_isquote(cmd[*i]))
	{
		if (!quote_token(token, cmd, i))
			return (1);
	}
	else if (ft_isoperator(&cmd[*i]))
	{
		if (!operator_token(token, cmd, i, ft_isoperator(&cmd[*i])))
			return (1);
	}
	else
	{
		if (!simple_token(token, cmd, i))
			return (1);
	}
	return (0);
}

static t_token	*get_token(char *cmd, int *i, bool space)
{
	t_token	*token;

	token = token_new("", 0, space);
	if (!token)
		return (NULL);
	if (choose_token(token, cmd, i))
	{
		free(token->content);
		free(token);
		return (NULL);
	}
	return (token);
}

void	tokenizer(t_token **tokens, char *cmd, t_pair *env)
{
	t_token	*token;
	int		i;
	bool	space;

	*tokens = NULL;
	i = 0;
	while (1)
	{
		while (ft_isblank(cmd[i]))
		{
			space = true;
			i++;
		}
		if (!cmd[i])
			break ;
		token = get_token(cmd, &i, space);
		if (!token)
		{
			g_exit_status = 1;
			exit_minishell(NULL, NULL, env);
		}
		token_add_back(tokens, token);
		if (!cmd[i])
			break ;
	}
}
