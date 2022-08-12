/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:51 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:52 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_out_last(t_process *process, int *i)
{
	if (process[*i].redirect_out)
	{
		if (dup2(process[*i].fd_out, STDOUT_FILENO) < 0)
			pipe_dup_error(process);
	}
	else if (process[*i - 1].redirect_out == 1)
	{
		if (process[*i].redirect_out)
		{
			if (dup2(process[*i].fd_out, STDOUT_FILENO) < 0)
				pipe_dup_error(process);
		}
		else
		{
			if (dup2(process[*i].tmp_out, STDOUT_FILENO) < 0)
				pipe_dup_error(process);
		}
	}
	else if (!process[*i - 1].redirect_out && !process[*i].redirect_out)
	{
		if (dup2(process[*i].tmp_out, STDOUT_FILENO) < 0)
			pipe_dup_error(process);
	}
}

static void	redirect_last(t_process *process, int *i)
{
	if (process[*i - 1].redirect_in)
	{
		if (process[*i].redirect_in)
		{
			if (dup2(process[*i].fd_in, STDIN_FILENO) < 0)
				pipe_dup_error(process);
		}
		else
		{
			if (dup2(process[*i - 1].fd_in, STDIN_FILENO) < 0)
				pipe_dup_error(process);
		}
	}
	else if (!process[*i - 1].redirect_in && !process[*i].redirect_in)
	{
		if (dup2(process[*i - 1].fd_in, STDIN_FILENO) < 0)
			pipe_dup_error(process);
	}
	else if (process[*i].redirect_in)
	{
		if (dup2(process[*i].fd_in, STDIN_FILENO) < 0)
			pipe_dup_error(process);
	}
	redirect_out_last(process, i);
}

static void	close_last_fds(t_process *process, int *i)
{
	if (*i)
	{
		close(process[*i - 1].fd_in);
		close(process[*i - 1].fd_out);
	}
	close(process[*i].fd_in);
	close(process[*i].fd_out);
}

void	last(t_process *process, int *i)
{
	signal(SIGINT, sigint_signal);
	process[*i].pid = fork();
	if (process[*i].pid < 0)
		fork_error(process);
	else if (!process[*i].pid)
	{
		signal(SIGQUIT, sig_quit);
		redirect_last(process, i);
		if (is_builtin(process, i))
			g_exit_status = check_builtins(process, i);
		else
			g_exit_status = execute(process, i);
		close(process[*i].fd_in);
		close(process[*i].fd_out);
		exit(g_exit_status);
	}
	wait_signal(process, i);
	close_last_fds(process, i);
	return_std(process, i);
}
