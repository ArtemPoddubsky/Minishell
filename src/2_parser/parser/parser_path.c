/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:56 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:57 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static char	*get_test_path(char *path, char *cmd)
{
	char	*slash;
	char	*res;

	slash = ft_strjoin(path, "/");
	if (!slash)
		return (NULL);
	res = ft_strjoin(slash, cmd);
	if (!res)
		return (NULL);
	free(slash);
	return (res);
}

static int	get_parser_path_loop(char **paths, char *cmd, t_process *process)
{
	char	*tmp;
	int		i;

	i = -1;
	while (paths[++i])
	{
		tmp = get_test_path(paths[i], cmd);
		if (!tmp)
			return (1);
		if (!access(tmp, F_OK | X_OK))
		{
			free_split(paths);
			process->path = tmp;
			return (0);
		}
		free(tmp);
	}
	free_split(paths);
	return (0);
}

static int	get_parser_path(t_process *process, char *cmd)
{
	t_pair	*path;
	char	**paths;

	if (!cmd)
		return (0);
	if (!access(cmd, F_OK | X_OK))
	{
		process->path = cmd;
		return (0);
	}
	path = get_env_value(process->env, "PATH");
	paths = ft_split(path->value, ':');
	if (!paths)
		return (1);
	return (get_parser_path_loop(paths, cmd, process));
}

int	parser_path(t_process *process)
{
	t_token	*util;

	util = process->tokens;
	while (util)
	{
		if (util->type == T_COMMAND && process->type == P_EXEC)
		{
			if (get_parser_path(process, util->content))
				return (1);
		}
		util = util->next;
	}
	return (0);
}
