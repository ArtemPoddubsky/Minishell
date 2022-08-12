/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:05 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:06 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	input(t_process *process, char *file, int flags)
{
	if (process->fd_in != -1)
		close(process->fd_in);
	process->fd_in = open(file, flags);
	process->redirect_in = true;
	if (process->fd_in == -1)
	{
		ft_putstr_fd(ERR_FILE, STDERR_FILENO);
		g_exit_status = 1;
	}
}

static void	output(t_process *process, char *file, int flags)
{
	if (process->fd_out != -1)
		close(process->fd_out);
	process->fd_out = open(file, flags, 0644);
	process->redirect_out = true;
	if (process->fd_out == -1)
	{
		ft_putstr_fd(ERR_FILE, STDERR_FILENO);
		g_exit_status = 1;
	}
}

int	parser_redirect(t_process *process)
{
	t_token	*util;

	util = process->tokens;
	while (util)
	{
		if (util->type == T_INPUT_F)
			input(process, util->content, O_RDONLY);
		else if (util->type == T_OUTPUT_F)
			output(process, util->content, O_RDWR | O_CREAT | O_TRUNC);
		else if (util->type == T_APPEND_F)
			output(process, util->content, O_WRONLY | O_CREAT | O_APPEND);
		else if (util->type == T_HEREDOC_D && parser_heredoc(process, util))
			return (1);
		util = util->next;
	}
	return (0);
}
