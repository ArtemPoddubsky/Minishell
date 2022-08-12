/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:42 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:47 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_signal(t_process *process, int *i)
{
	waitpid(process[*i].pid, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
	else if (WIFSIGNALED(g_exit_status))
		g_exit_status = WTERMSIG(g_exit_status) + 128;
	if (g_exit_status == 131)
		ft_putstr_fd("Quit: 3\n", 2);
	set_signal();
}

int	built_or_exec(t_process *process, int *i)
{
	int	ret;

	if (is_builtin(process, i))
		ret = check_builtins(process, i);
	else
		ret = execute(process, i);
	return (ret);
}

static int	simple_child(t_process *process, int *i)
{
	int	ret;

	if (process[*i].redirect_in == 1)
	{
		if (dup2(process[*i].fd_in, STDIN_FILENO) < 0)
			pipe_dup_error(process);
	}
	if (process[*i].redirect_out == 1)
	{
		if (dup2(process[*i].fd_out, STDOUT_FILENO) < 0)
			pipe_dup_error(process);
	}
	ret = built_or_exec(process, i);
	close(process[*i].fd_in);
	close(process[*i].fd_out);
	return_std(process, i);
	return (ret);
}

void	simple_cmd(t_process *process)
{
	int	i;

	i = 0;
	if (!is_builtin(process, &i))
	{
		signal(SIGINT, sigint_signal);
		process[i].pid = fork();
		if (process[i].pid < 0)
			fork_error(process);
		if (!process[i].pid)
		{
			signal(SIGQUIT, sig_quit);
			g_exit_status = simple_child(process, &i);
			exit(g_exit_status);
		}
		wait_signal(process, &i);
		close(process[i].fd_in);
		close(process[i].fd_out);
	}
	else
		g_exit_status = simple_child(process, &i);
	return_std(process, &i);
}

int	executor(t_process *process)
{
	int	i;

	i = -1;
	while (!process[++i].last)
	{
		if (!i && process[i + 1].last)
			simple_cmd(process);
		else if (!process[i + 1].last)
			not_last(process, &i);
		else
			last(process, &i);
	}
	return (g_exit_status);
}
