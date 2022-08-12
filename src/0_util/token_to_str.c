/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:48:46 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 19:48:52 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_to_str(t_token *token)
{
	t_token	*util;
	int		c;
	char	**res;
	int		i;

	util = token;
	c = 0;
	while (util)
	{
		util = util->next;
		c++;
	}
	res = malloc(sizeof(char *) * (c + 1));
	i = 0;
	while (token)
	{
		res[i] = ft_strdup(token->content);
		token = token->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
