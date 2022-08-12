/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:18 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:19 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_error(t_process *process)
{
	perror("minishell: Resource temporarily unavailable\n");
	g_exit_status = 11;
	exit_minishell(process, process->tokens, process->env);
}

void	pipe_dup_error(t_process *process)
{
	perror("minishell: too many open files\n");
	g_exit_status = 24;
	exit_minishell(process, process->tokens, process->env);
}
