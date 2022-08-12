/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:45 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:46 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_process *process, int *i)
{
	if (!ft_strcmp(process[*i].tokens->content, "echo"))
		return (1);
	else if (!ft_strcmp(process[*i].tokens->content, "pwd"))
		return (1);
	else if (!ft_strcmp(process[*i].tokens->content, "cd"))
		return (1);
	else if (!ft_strcmp(process[*i].tokens->content, "export"))
		return (1);
	else if (!ft_strcmp(process[*i].tokens->content, "unset"))
		return (1);
	else if (!ft_strcmp(process[*i].tokens->content, "env"))
		return (1);
	else if (!ft_strcmp(process[*i].tokens->content, "exit"))
		return (1);
	return (0);
}

int	check_builtins(t_process *process, int *i)
{
	if (!ft_strcmp(process[*i].tokens->content, "echo"))
		return (echo(process[*i].tokens->next));
	else if (!ft_strcmp(process[*i].tokens->content, "pwd"))
		return (pwd());
	else if (!ft_strcmp(process[*i].tokens->content, "cd"))
		return (cd(process, i));
	else if (!ft_strcmp(process[*i].tokens->content, "export"))
		return (export(process[*i].tokens->next, process[*i].env));
	else if (!ft_strcmp(process[*i].tokens->content, "unset"))
		return (unset(process[*i].tokens->next, process[*i].env));
	else if (!ft_strcmp(process[*i].tokens->content, "env"))
		return (print_envir(process[*i].env));
	else if (!ft_strcmp(process[*i].tokens->content, "exit"))
		exit_builtin(process, i);
	return (1);
}

int	check_exec(char *str, int flag)
{
	struct stat	buf;
	int			ret;

	ret = 0;
	stat(str, &buf);
	if (buf.st_mode & S_IFDIR)
	{
		if (flag == 1)
			ft_putstr_fd(ft_strjoin("minishell: ",
					ft_strjoin(str, ": is a directory\n")), 2);
		ret = 126;
		return (ret);
	}
	return (ret);
}

int	execute(t_process *process, int *i)
{
	int		ret;
	char	**tokens_s;
	char	**env_s;

	tokens_s = NULL;
	env_s = NULL;
	ret = exec_error(process[*i].tokens->content, process[*i].path);
	if (ret)
		return (ret);
	tokens_s = token_to_str(process[*i].tokens);
	env_s = convert_to_double(process[*i].env);
	ret = execve(process[*i].path, tokens_s, env_s);
	free_mas(tokens_s);
	free_mas(env_s);
	return (ret);
}
