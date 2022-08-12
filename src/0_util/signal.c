/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:30 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:31 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigint_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(1);
	}
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal(void)
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, SIG_IGN);
}
