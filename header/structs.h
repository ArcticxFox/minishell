/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:15:54 by ejones            #+#    #+#             */
/*   Updated: 2026/06/29 16:55:40 by ejones           ###   ########.fr       */
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

typedef struct s_pipe_state
{
	int		**pipes;
	int		n_cmds;
	int		index;
	pid_t	*pids;
}	t_pipe_state;

typedef struct s_redir
{
	t_tk_type		type;
	int				heredoc_fd;
	char			*delimiter;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir			*redir;
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
	t_cmd	*head;
	char	**env;
	int		should_exit;
}	t_shell;

typedef struct s_builtin
{
	char	*name;
	int		(*f)(char **args, t_shell *shell);
}	t_builtin;

#endif
