/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:34:20 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:34:21 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef struct s_pair
{
	char			*key;
	char			*value;
	struct s_pair	*next;
	struct s_pair	*previous;
}	t_pair;

enum	e_process_type
{
	P_ECHO = 1,
	P_CD = 2,
	P_PWD = 3,
	P_EXPORT = 4,
	P_UNSET = 5,
	P_ENV = 6,
	P_EXIT = 7,
	P_EXEC = 8
};

enum	e_token_type
{
	T_QUOTE = 1,
	T_PIPE = 2,
	T_INPUT_R = 3,
	T_INPUT_F = 4,
	T_OUTPUT_R = 5,
	T_OUTPUT_F = 6,
	T_HEREDOC_R = 7,
	T_HEREDOC_D = 8,
	T_APPEND_R = 9,
	T_APPEND_F = 10,
	T_BUILTIN = 11,
	T_COMMAND = 12,
	T_EMPTY = 13
};

typedef struct s_token
{
	char			*content;
	short			type;
	bool			space;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_process
{
	t_pair	*env;
	t_token	*tokens;

	char	*path;

	short	type;
	bool	last;

	int		fd_in;
	int		fd_out;
	int		pid;

	int		tmp_in;
	int		tmp_out;

	bool	redirect_in;
	bool	redirect_out;

	char	**env_char;
}	t_process;

#endif
