/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:11 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:12 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_process *processes)
{
	int	i;

	i = -1;
	while (!processes[++i].last)
	{
		if (parser_env(processes[i]))
			exit_minishell(processes, processes->tokens, processes->env);
		if (parser_types(processes[i]))
			return (1);
		if (parser_quotes(processes[i]))
			exit_minishell(processes, processes->tokens, processes->env);
		parser_functions(&processes[i]);
		if (parser_redirect(&processes[i]))
			exit_minishell(processes, processes->tokens, processes->env);
		if (parser_path(&processes[i]))
			exit_minishell(processes, processes->tokens, processes->env);
	}
	return (0);
}
