/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:23 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:24 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_token(t_token *token, char *cmd, int *i)
{
	token->type = T_QUOTE;
	token->content = ft_strnjoin(token->content, &cmd[*i], 1);
	if (!token->content)
		return (0);
	(*i)++;
	while (cmd[*i])
	{
		token->content = ft_strnjoin(token->content, &cmd[*i], 1);
		if (!token->content)
			return (0);
		if (ft_isquote(cmd[*i]))
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (1);
}

int	operator_token(t_token *token, char *cmd, int *i, int type)
{
	token->type = type;
	if (type == T_PIPE || type == T_INPUT_R || type == T_OUTPUT_R)
	{
		token->content = ft_strnjoin(token->content, &cmd[*i], 1);
		if (!token->content)
			return (0);
		(*i)++;
	}
	else
	{
		token->content = ft_strnjoin(token->content, &cmd[*i], 2);
		if (!token->content)
			return (0);
		*i += 2;
	}
	return (1);
}

int	simple_token(t_token *token, char *cmd, int *i)
{
	token->type = T_COMMAND;
	while (cmd[*i] && cmd[*i] != ' ' && !ft_isoperator(&cmd[*i]))
	{
		token->content = ft_strnjoin(token->content, &cmd[*i], 1);
		if (!token->content)
			return (0);
		(*i)++;
	}
	return (1);
}
