/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:34:34 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:34:35 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_signal(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sig_quit(int signo)
{
	if (signo == SIGQUIT)
	{
		g_exit_status = WTERMSIG(g_exit_status) + 128;
		rl_on_new_line();
		exit(g_exit_status);
	}
}
