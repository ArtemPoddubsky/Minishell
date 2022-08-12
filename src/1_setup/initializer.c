/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:36 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:37 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_env(t_pair **env, char **envp)
{
	int		i;
	char	**tmp;

	i = -1;
	while (envp[++i])
	{
		tmp = split_env(envp[i]);
		if (!tmp)
		{
			free_splitted_env(tmp);
			return (1);
		}
		if (!add_env(env, tmp[0], tmp[1]))
		{
			free_env_pairs(*env);
			free_splitted_env(tmp);
			return (1);
		}
		free_splitted_env(tmp);
	}
	return (0);
}

static int	set_term(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (1);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (1);
	return (0);
}

void	set_minishell(t_pair **env, char **envp)
{
	g_exit_status = 0;
	set_signal();
	*env = NULL;
	if (set_env(env, envp))
	{
		ft_putstr_fd(ERR_MALLOC, STDERR_FILENO);
		g_exit_status = 1;
		exit_minishell(NULL, NULL, NULL);
	}
	if (set_term())
	{
		ft_putstr_fd(ERR_TERMIOS, STDERR_FILENO);
		g_exit_status = 1;
		exit_minishell(NULL, NULL, *env);
	}
}
