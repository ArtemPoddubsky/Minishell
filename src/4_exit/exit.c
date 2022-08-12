/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:35 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:36 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_process *process, t_token *tokens, t_pair *env)
{
	(void)process;
	free_tokens(tokens);
	free_env_pairs(env);
	rl_clear_history();
	exit(g_exit_status);
}
