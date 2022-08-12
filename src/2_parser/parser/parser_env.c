/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:46 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:47 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_variable(char **res, char *cmd, int *i, t_pair *env)
{
	int		len;
	char	*key;
	t_pair	*env_p;
	char	*value;

	(*i)++;
	len = 0;
	while (cmd[*i + len] && !ft_isblank(cmd[*i + len]))
		len++;
	key = ft_substr(&cmd[*i], 0, len);
	env_p = get_env_value(env, key);
	if (!env_p)
		value = ft_strdup("");
	else
		value = ft_strdup(env_p->value);
	free(key);
	*res = ft_strjoin_free_second(*res, value);
	*i += len;
}

static void	expand_question(char **res, int *i)
{
	char	*exit_status;

	exit_status = ft_itoa(g_exit_status);
	*res = ft_strjoin_free_second(*res, exit_status);
	*i += 2;
}

static void	choose_expander(char **res, char *cmd, int *i, t_pair *env)
{
	(void)env;
	if (cmd[*i + 1] == '?')
		expand_question(res, i);
	else if (ft_isquote(cmd[*i + 1]))
		(*i)++;
	else if (cmd[*i + 1] >= '0' && cmd[*i + 1] <= '9')
		*i += 2;
	else if (!ft_isalnum(cmd[*i + 1]))
	{
		*res = ft_strnjoin(*res, &cmd[*i], 2);
		*i += 1;
	}
	else
		expand_variable(res, cmd, i, env);
}

static int	expand_env(char **cmd, t_pair *env)
{
	char	*res;
	int		quote;
	int		i;

	res = ft_strdup("");
	if (!res)
		return (1);
	quote = 0;
	i = 0;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '\'')
			quote = !quote;
		if ((*cmd)[i] == '$' && !quote)
			choose_expander(&res, *cmd, &i, env);
		else
			res = ft_strnjoin(res, &(*cmd)[i], 1);
		if (!res)
			return (1);
		i++;
	}
	free(*cmd);
	*cmd = res;
	return (0);
}

int	parser_env(t_process process)
{
	t_token	*util;

	util = process.tokens;
	while (util)
	{
		if (ft_strchr(util->content, '$'))
		{
			if (expand_env(&util->content, process.env))
				return (1);
			if (!util->content[0])
				util->type = T_EMPTY;
		}
		util = util->next;
	}
	return (0);
}
