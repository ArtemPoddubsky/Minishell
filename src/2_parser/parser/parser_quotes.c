/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:01 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:02 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quotes(char **cmd)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	res = malloc(ft_strlen(*cmd) - 2);
	if (!res)
		return (1);
	i = 0;
	j = 0;
	quote = 0;
	while ((*cmd)[i])
	{
		if (ft_isquote((*cmd)[i]))
			quote = (*cmd)[i];
		else if (!quote || (*cmd)[i] != quote)
			res[j++] = (*cmd)[i];
		else if ((*cmd)[i] == quote)
			quote = 0;
		i++;
	}
	res[j] = '\0';
	free(*cmd);
	*cmd = res;
	return (0);
}

int	parser_quotes(t_process process)
{
	t_token	*util;

	util = process.tokens;
	while (util)
	{
		if (util->type == T_QUOTE)
		{
			if (remove_quotes(&util->content))
				return (1);
		}
		util = util->next;
	}
	return (0);
}
