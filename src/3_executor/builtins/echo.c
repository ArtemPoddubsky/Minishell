/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:37:01 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:37:02 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_quotes(char *content)
{
	if (ft_strlen(content) == 2
		&& ((content[0] == '"' || content[0] == '\'')
			&& (content[1] == '"' || content[1] == '\'')))
		return (0);
	return (1);
}

static int	echo_loop(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!is_empty_quotes(content))
			break ;
		if (content[i] == '"' || content[i] == '\'')
			i++;
		write(1, &content[i], 1);
		i++;
	}
	return (1);
}

int	echo(t_token *tokens)
{
	int		flag;
	int		i;

	if (tokens && !ft_strncmp(tokens->content, "-n", 2)
		&& ft_strlen(tokens->content) == 2)
	{
		flag = 1;
		tokens = tokens->next;
	}
	else
		flag = 0;
	i = 0;
	while (tokens && (tokens->type == T_COMMAND || tokens->type == T_QUOTE))
	{
		if (tokens->space == true && i)
			write(1, " ", 1);
		if (!echo_loop(tokens->content))
			return (0);
		tokens = tokens->next;
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
