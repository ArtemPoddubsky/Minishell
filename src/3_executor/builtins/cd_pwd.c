/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:09:20 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 17:09:21 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_pair *env)
{
	char	*pwd;
	t_pair	*old;
	t_pair	*current;

	old = get_env_value(env, "OLDPWD");
	current = get_env_value(env, "PWD");
	if (old && old->value != NULL)
		free(old->value);
	if (old)
		old->value = ft_strdup(current->value);
	if (current && current->value)
		free(current->value);
	if (current)
	{
		pwd = (char *)malloc(sizeof(char) * MAXDIR);
		getcwd(pwd, MAXDIR);
		current->value = pwd;
	}
}

static int	check_dir(char *str)
{
	struct stat	buf;
	int			ret;

	ret = 0;
	stat(str, &buf);
	if (buf.st_mode & S_IFDIR)
		return (ret);
	else
	{
		ft_putstr_fd(ft_strjoin("minishell: ",
				ft_strjoin(str, ": Not a directory\n")), 2);
		ret = 1;
	}
	return (ret);
}

static int	empty_cd(t_pair *env)
{
	t_pair	*tmp;

	tmp = get_env_value(env, "HOME");
	if (!tmp)
	{
		perror("minishell: cd: HOME not set");
		return (1);
	}
	if (chdir(tmp->value) == -1)
	{
		perror("minishell: cd: permission denied");
		return (1);
	}
	else
		update_pwd(env);
	return (0);
}

int	cd(t_process *process, int *i)
{
	DIR		*dir;

	process[*i].tokens = process[*i].tokens->next;
	if (!process[*i].tokens)
		return (empty_cd(process[*i].env));
	if (check_dir(process[*i].tokens->content))
		return (1);
	dir = opendir(process[*i].tokens->content);
	if (!dir)
		return (1);
	if (chdir(process[*i].tokens->content) == -1)
	{
		perror("minishell: cd: permission denied");
		return (1);
	}
	else
		update_pwd(process[*i].env);
	closedir(dir);
	return (0);
}

int	pwd(void)
{
	char	dir[MAXDIR];

	getcwd(dir, MAXDIR);
	write(1, dir, ft_strlen(dir));
	write(1, "\n", 1);
	return (0);
}
