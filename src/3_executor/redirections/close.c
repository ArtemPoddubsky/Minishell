/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:36:49 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:36:50 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_not_last(t_process *process, int *i, int fd[][2])
{
	close(process[*i].fd_in);
	close(process[*i].fd_out);
	close(fd[0][1]);
	close(fd[0][0]);
}

void	return_std(t_process *process, int *i)
{
	dup2(process[*i].tmp_out, 1);
	dup2(process[*i].tmp_in, 0);
	close(process[*i].tmp_in);
	close(process[*i].tmp_out);
}
