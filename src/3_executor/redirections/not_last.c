/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:54 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:58 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_first_out(t_process *process, int *i, int fd[][2])
{
	if (process[*i].redirect_out == 1)
	{
		fd[0][1] = dup(process[*i].fd_out);
		if (fd[0][1] < 0)
			pipe_dup_error(process);
		close(process[*i].fd_out);
		if (dup2(fd[0][1], STDOUT_FILENO) < 0)
			pipe_dup_error(process);
	}
	else
	{
		if (dup2(fd[0][1], STDOUT_FILENO) < 0)
			pipe_dup_error(process);
	}
}

static void	redirect_first(t_process *process, int *i, int fd[][2])
{
	if (process[*i].redirect_in)
	{
		fd[0][0] = dup(process[*i].fd_in);
		if (fd[0][0] < 0)
			pipe_dup_error(process);
		close(process[*i].fd_in);
		if (dup2(fd[0][0], STDIN_FILENO) < 0)
			pipe_dup_error(process);
	}
	else
	{
		if (dup2(fd[0][0], STDIN_FILENO) < 0)
			pipe_dup_error(process);
	}
	redirect_first_out(process, i, fd);
}

static void	redirect_not_last(t_process *process, int *i, int fd[][2])
{
	if (*i == 0)
		redirect_first(process, i, fd);
	else
	{
		if (process[*i].redirect_in)
			redir_1_nl_in(process, i, fd);
		else if (process[*i - 1].redirect_in)
			redir_2_nl_in(process, i, fd);
		else if (!process[*i - 1].redirect_in && !process[*i].redirect_in)
			redir_3_nl_in(process, i, fd);
		if (process[*i].redirect_out == 1)
			redir_1_nl_out(process, i, fd);
		else if (process[*i - 1].redirect_out)
			redir_2_nl_out(process, i, fd);
		else if (!process[*i - 1].redirect_out && !process[*i].redirect_out)
		{
			if (dup2(fd[0][1], STDOUT_FILENO) < 0)
				pipe_dup_error(process);
		}
	}
}

void	not_last(t_process *process, int *i)
{
	int	fd[2];

	signal(SIGINT, sigint_signal);
	if (pipe(fd) < 0)
		pipe_dup_error(process);
	process[*i].pid = fork();
	if (process[*i].pid < 0)
		fork_error(process);
	else if (!process[*i].pid)
	{
		signal(SIGQUIT, sig_quit);
		redirect_not_last(process, i, &fd);
		g_exit_status = built_or_exec(process, i);
		close_not_last(process, i, &fd);
		exit(g_exit_status);
	}
	wait_signal(process, i);
	close(fd[1]);
	process[*i].fd_in = dup(fd[0]);
	if (process[*i].fd_in < 0)
		pipe_dup_error(process);
	close(fd[0]);
	if (*i)
		close(process[*i - 1].fd_in);
}
