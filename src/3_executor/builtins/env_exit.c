/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:37:04 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 17:09:05 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_envir(t_pair *env)
{
	while (env)
	{
		write(1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}

static void	choose_exit(char *str, int i, int other, int first)
{
	if (i == 1 && !other)
	{
		g_exit_status = (unsigned char)ft_atoi(str);
		return ;
	}
	if (i == 0 && !other)
		return ;
	ft_putstr_fd("minishell: exit", 2);
	if (i >= 1 && first)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_status = 255;
		return ;
	}
	else if (i > 1 && !first)
	{
		ft_putstr_fd(": too many arguments\n", 2);
		g_exit_status = 1;
	}
	else
		ft_putstr_fd("\n", 1);
}

void	exit_builtin(t_process *process, int *i)
{
	int		counter;
	int		other;
	int		first;
	char	*tmp;

	counter = 0;
	other = 0;
	first = 0;
	process[*i].tokens = process[*i].tokens->next;
	if (process[*i].tokens)
	{
		tmp = process[*i].tokens->content;
		while (process[*i].tokens && process[*i].tokens->content)
		{
			if (counter == 0 && str_is_digits(process[*i].tokens->content) == 0)
				first = 1;
			if (str_is_digits(process[*i].tokens->content) == 0)
				other = 1;
			counter++;
			process[*i].tokens = process[*i].tokens->next;
		}
		choose_exit(tmp, counter, other, first);
	}
	exit_minishell(process, process->tokens, process->env);
}
