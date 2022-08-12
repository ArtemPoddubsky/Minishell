/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:18 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:19 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_process(t_process *process, t_pair *env)
{
	process->env = env;
	process->fd_in = 0;
	process->fd_out = 1;
	process->tmp_out = dup(1);
	process->tmp_in = dup(0);
	process->redirect_in = false;
	process->redirect_out = false;
}

static void	set_process_tokens_zero(t_process *process, t_token *tokens)
{
	t_token	*pipe_s;
	t_token	*pipe_e;

	pipe_s = tokens;
	while (tokens->next)
	{
		if (tokens->next->type == T_PIPE)
			break ;
		tokens = tokens->next;
	}
	pipe_e = tokens->next;
	token_cut(&process->tokens, pipe_s, pipe_e);
}

static void	process_loop(t_process *process, t_token *tokens, int i)
{
	int		curr_process;
	t_token	*pipe_s;
	t_token	*pipe_e;

	curr_process = 0;
	while (tokens)
	{
		if (tokens->type == T_PIPE)
		{
			curr_process++;
			if (curr_process == i)
			{
				pipe_s = tokens->next;
				while (tokens->next)
				{
					if (tokens->next->type == T_PIPE)
						break ;
					tokens = tokens->next;
				}
				pipe_e = tokens->next;
			}
		}
		tokens = tokens->next;
	}
	token_cut(&process->tokens, pipe_s, pipe_e);
}

static void	set_process_tokens(t_process *process, t_token *tokens, int i)
{
	if (i == 0)
	{
		set_process_tokens_zero(process, tokens);
		return ;
	}
	process_loop(process, tokens, i);
}

void	processer(t_process **processes, t_token *tokens, t_pair *env)
{
	int	c;
	int	i;

	c = processer_count(tokens);
	*processes = ft_calloc(c + 1, sizeof(t_process));
	if (!*processes)
		exit_minishell(NULL, tokens, env);
	i = 0;
	while (i < c)
	{
		set_process(&(*processes)[i], env);
		set_process_tokens(&(*processes)[i], tokens, i);
		i++;
	}
	(*processes)[i].last = true;
	free_tokens(tokens);
}
