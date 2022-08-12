/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:37:18 by lholdo            #+#    #+#             */
/*   Updated: 2022/08/10 16:34:14 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*input(t_pair *env)
{
	char	*cmd;
	size_t	i;

	cmd = readline(PROMPT_NORMAL);
	if (!cmd)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "exit\n", 5);
		exit_minishell(NULL, NULL, env);
	}
	i = 0;
	while (cmd[i] && ft_isblank(cmd[i]))
		i++;
	if (i == ft_strlen(cmd))
		return (NULL);
	return (cmd);
}

static void	main_loop(t_pair *env)
{
	char		*cmd;
	t_token		*tokens;
	t_process	*processes;

	while (21)
	{
		cmd = input(env);
		if (cmd && *cmd)
		{
			add_history(cmd);
			if (syntax_error(cmd))
			{
				free(cmd);
				continue ;
			}
			tokenizer(&tokens, cmd, env);
			free(cmd);
			processer(&processes, tokens, env);
			if (parser(processes))
				continue ;
			g_exit_status = executor(processes);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pair		*env;

	if (!argc || !argv)
		return (1);
	set_minishell(&env, envp);
	main_loop(env);
	free_env_pairs(env);
	return (g_exit_status);
}
