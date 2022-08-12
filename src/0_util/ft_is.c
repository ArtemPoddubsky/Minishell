/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:35:23 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:35:24 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isoperator_ch(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

int	ft_isquote(int c)
{
	return (c == '\'' || c == '"');
}

int	ft_isoperator(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (len != 1 && !ft_strncmp(cmd, HEREDOC_R, 2))
		return (T_HEREDOC_R);
	else if (len != 1 && !ft_strncmp(cmd, APPEND_R, 2))
		return (T_APPEND_R);
	else if (!ft_strncmp(cmd, INPUT_R, 1))
		return (T_INPUT_R);
	else if (!ft_strncmp(cmd, OUTPUT_R, 1))
		return (T_OUTPUT_R);
	else if (!ft_strncmp(cmd, PIPE, 1))
		return (T_PIPE);
	return (0);
}
