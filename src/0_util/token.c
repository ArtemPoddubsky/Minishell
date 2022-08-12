/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:33 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:34 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *content, int type, int space)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->type = type;
	token->space = space;
	return (token);
}

void	token_add_back(t_token **head, t_token *new)
{
	t_token	*util;

	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		util = *head;
		while (util->next)
			util = util->next;
		util->next = new;
		new->previous = util;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*util;

	while (tokens)
	{
		util = tokens;
		free(tokens->content);
		tokens = tokens->next;
		free(util);
	}
}

void	token_cut(t_token **head, t_token *start, t_token *end)
{
	while (start != end)
	{
		token_add_back(head, token_new(start->content, start->type,
				start->space));
		start = start->next;
	}
}

t_token	*token_last(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}
