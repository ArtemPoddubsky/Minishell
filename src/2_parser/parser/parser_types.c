/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:08 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:09 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(int token_type)
{
	return (token_type == T_INPUT_R || token_type == T_OUTPUT_R
		|| token_type == T_HEREDOC_R || token_type == T_APPEND_R);
}

static int	types_syntax_error(void)
{
	ft_putstr_fd(ERR_OPERATOR, STDERR_FILENO);
	g_exit_status = 2;
	return (1);
}

static int	types_ambiguous_error(void)
{
	ft_putstr_fd(ERR_AMBIGUOUS, STDERR_FILENO);
	g_exit_status = 2;
	return (1);
}

int	parser_types(t_process process)
{
	t_token	*util;

	util = process.tokens;
	while (util)
	{
		if (is_redirect(util->type))
		{
			if (!util->next)
				return (types_syntax_error());
			else if (util->next->type == T_EMPTY)
				return (types_ambiguous_error());
			if (util->type == T_HEREDOC_R)
				util->next->type = T_HEREDOC_D;
			else if (util->type == T_INPUT_R)
				util->next->type = T_INPUT_F;
			else if (util->type == T_OUTPUT_R)
				util->next->type = T_OUTPUT_F;
			else if (util->type == T_APPEND_R)
				util->next->type = T_APPEND_F;
			else
				return (types_syntax_error());
		}
		util = util->next;
	}
	return (0);
}
