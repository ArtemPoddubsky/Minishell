/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:52 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:53 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(int fd, char *delimeter)
{
	char	*line;

	set_signal_heredoc();
	while (21)
	{
		line = readline(PROMPT_HEREDOC);
		if (!line)
		{
			ft_putstr_fd(WARN_HEREDOC_EOF, STDERR_FILENO);
			close(fd);
			exit(0);
		}
		else if (!ft_strncmp(line, delimeter, ft_strlen(line)))
		{
			free(line);
			close(fd);
			exit(0);
		}
		else if (line)
		{
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
			free(line);
		}
	}
}

int	parser_heredoc(t_process *process, t_token *delimeter)
{
	pid_t	pid;
	int		status;

	process->fd_in = open(TMP_HEREDOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	process->redirect_in = 1;
	if (process->fd_in == -1)
	{
		ft_putstr_fd(ERR_FILE, STDERR_FILENO);
		g_exit_status = 1;
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		child_process(process->fd_in, delimeter->content);
	wait(&status);
	if (!WIFEXITED(status))
	{
		g_exit_status = 1;
		return (1);
	}
	set_signal();
	process->fd_in = open(TMP_HEREDOC, O_RDONLY);
	unlink(TMP_HEREDOC);
	return (0);
}
