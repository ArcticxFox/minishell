/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:15:54 by ejones            #+#    #+#             */
/*   Updated: 2026/05/10 20:24:13 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_filetype
{
	IS_FILE = 1,
	NOT_FILE
}	t_filetype;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_tk_type;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				expand;
	t_filetype		filetype;
	t_tk_type		tk_type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	int				expand;
	char			*value;
	t_tk_type		type;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	**env;
}	t_shell;

typedef struct s_builtin
{
	char	*name;
	int		(*f)(char **args, t_shell *shell);
}	t_builtin;

#endif
