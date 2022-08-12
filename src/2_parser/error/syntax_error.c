/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:41 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:42 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_quote(char *cmd, int *i)
{
	char	quote;

	quote = cmd[(*i)++];
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (!cmd[*i])
	{
		ft_putstr_fd(ERR_QUOTE, STDERR_FILENO);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

static int	syntax_pipe(char *cmd, int i)
{
	int	err;
	int	i_init;

	err = 0;
	if (i == 0)
		err = 1;
	i_init = i;
	while (i >= -1 && ft_isblank(cmd[--i]))
		;
	if (i < 0 || ft_isoperator_ch(cmd[i]))
		err = 1;
	i = i_init;
	while (cmd[i] && ft_isblank(cmd[++i]))
		;
	if (!cmd[i] || ft_isoperator_ch(cmd[i]))
		err = 1;
	if (err)
	{
		ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

static int	syntax_redirect_error(void)
{
	ft_putstr_fd(ERR_PIPE, STDERR_FILENO);
	g_exit_status = 2;
	return (1);
}

static int	syntax_redirect(char *cmd, int i)
{
	int		err;
	int		i_i;
	char	a;

	err = 0;
	if (i == 0)
		err = 1;
	i_i = i;
	a = cmd[i];
	while (i >= -1 && ft_isblank(cmd[--i]))
		;
	if (i < 0 || (ft_isoperator_ch(cmd[i]) && !(i == i_i - 1 && a == cmd[i])))
		err = 1;
	i = i_i;
	a = cmd[i];
	while (cmd[i] && ft_isblank(cmd[++i]))
		;
	if (!cmd[i] || (ft_isoperator_ch(cmd[i]) && !(i == i_i + 1 && a == cmd[i])))
		err = 1;
	if (err)
		return (syntax_redirect_error());
	return (0);
}

int	syntax_error(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		while (ft_isblank(cmd[i]))
			i++;
		if (!cmd[i])
			return (0);
		if (ft_isquote(cmd[i]))
		{
			if (syntax_quote(cmd, &i))
				return (1);
		}
		else if (cmd[i] == '|')
		{
			if (syntax_pipe(cmd, i))
				return (1);
		}
		else if (ft_isoperator_ch(cmd[i]))
			if (syntax_redirect(cmd, i))
				return (1);
		i++;
	}
	return (0);
}
