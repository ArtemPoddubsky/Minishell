/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processer_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:15 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:16 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	processer_count(t_token *tokens)
{
	int	c;

	c = 1;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
			c++;
		tokens = tokens->next;
	}
	return (c);
}
