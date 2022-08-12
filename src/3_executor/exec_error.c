/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:55:05 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 19:05:23 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(char *str)
{
	ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", str),
			": command not found\n"), 2);
}

void	permission_denied(char *str)
{
	ft_putstr_fd(ft_strjoin("minishell: ",
			ft_strjoin(str, ": Permission denied\n")), 2);
}

void	no_such_file_or_dir(char *str)
{
	ft_putstr_fd(ft_strjoin("minishell: ",
			ft_strjoin(str, ": No such file or directory\n")), 2);
}

static int	if_err_path(char *content)
{
	int	ret;

	ret = 0;
	if (access(content, 0))
	{
		no_such_file_or_dir(content);
		ret = 127;
	}
	else if (!access(content, 0) && check_exec(content, 1))
		ret = 126;
	else if (!access(content, 0) && !check_exec(content, 1)
		&& access(content, 1))
	{
		permission_denied(content);
		ret = 126;
	}	
	return (ret);
}

int	exec_error(char *content, char *path)
{
	int	ret;

	ret = 0;
	if (ft_strchr(content, '/'))
		ret = if_err_path(content);
	else
	{
		if (check_exec(path, 0) || access(path, 0))
		{
			command_not_found(content);
			ret = 127;
		}
	}
	return (ret);
}
