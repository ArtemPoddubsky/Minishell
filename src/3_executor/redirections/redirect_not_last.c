/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_not_last.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:57 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:58 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_1_nl_in(t_process *process, int *i, int fd[][2])
{
	fd[0][0] = dup(process[*i].fd_in);
	if (fd[0][0] < 0)
		pipe_dup_error(process);
	close(process[*i].fd_in);
	if (dup2(fd[0][0], STDIN_FILENO) < 0)
		pipe_dup_error(process);
}

void	redir_2_nl_in(t_process *process, int *i, int fd[][2])
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
		fd[0][0] = dup(process[*i - 1].fd_in);
		if (fd[0][0] < 0)
			pipe_dup_error(process);
		close(process[*i - 1].fd_in);
		if (dup2(fd[0][0], STDIN_FILENO) < 0)
			pipe_dup_error(process);
	}
}

void	redir_3_nl_in(t_process *process, int *i, int fd[][2])
{
	fd[0][0] = dup(process[*i - 1].fd_in);
	if (fd[0][0] < 0)
		pipe_dup_error(process);
	close(process[*i - 1].fd_in);
	if (dup2(fd[0][0], STDIN_FILENO) < 0)
		pipe_dup_error(process);
}

void	redir_1_nl_out(t_process *process, int *i, int fd[][2])
{
	fd[0][1] = dup(process[*i].fd_out);
	if (fd[0][1] < 0)
		pipe_dup_error(process);
	close(process[*i].fd_out);
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		pipe_dup_error(process);
}

void	redir_2_nl_out(t_process *process, int *i, int fd[][2])
{
	if (process[*i].redirect_out)
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
