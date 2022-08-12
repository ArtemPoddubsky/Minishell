/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:34:12 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/22 17:34:15 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define IN 0
# define OUT 1

# define PROMPT_NORMAL "$$$ "
# define PROMPT_HEREDOC "> "

# define INPUT_R "<"
# define OUTPUT_R ">"
# define HEREDOC_R "<<"
# define APPEND_R ">>"
# define PIPE "|"

# define ERR_MALLOC "CRITICAL ERROR: malloc failure.\n"
# define ERR_TERMIOS "CRITICAL ERROR: termios failure.\n"
# define ERR_QUOTE "SYNTAX ERROR: unclosed quote.\n"
# define ERR_PIPE "SYNTAX ERROR: unclosed pipe.\n"
# define ERR_OPERATOR "SYNTAX ERROR: unexpected token.\n"
# define ERR_AMBIGUOUS "SYNTAX ERROR: ambiguous redirect.\n"
# define ERR_FILE "CRITICAL ERROR: file couldn't be opened.\n"

# define WARN_HEREDOC_EOF "WARNING: heredoc delimetered by EOF.\n"

# define TMP_HEREDOC "tmp.hdoc"

#endif
