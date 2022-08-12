/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:49 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:50 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_functions(t_process *process)
{
	char	*s;

	s = process->tokens->content;
	if (!ft_strncmp(s, "echo", ft_strlen(s)) && ft_strlen(s) == 4)
		process->type = P_ECHO;
	else if (!ft_strncmp(s, "cd", ft_strlen(s)) && ft_strlen(s) == 2)
		process->type = P_CD;
	else if (!ft_strncmp(s, "pwd", ft_strlen(s)) && ft_strlen(s) == 3)
		process->type = P_PWD;
	else if (!ft_strncmp(s, "export", ft_strlen(s)) && ft_strlen(s) == 6)
		process->type = P_EXPORT;
	else if (!ft_strncmp(s, "unset", ft_strlen(s)) && ft_strlen(s) == 5)
		process->type = P_UNSET;
	else if (!ft_strncmp(s, "env", ft_strlen(s)) && ft_strlen(s) == 3)
		process->type = P_ENV;
	else if (!ft_strncmp(s, "exit", ft_strlen(s)) && ft_strlen(s) == 4)
		process->type = P_EXIT;
	else
		process->type = P_EXEC;
}
