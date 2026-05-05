/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:59:50 by ejones            #+#    #+#             */
/*   Updated: 2026/05/05 15:26:59 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/header/libft.h"

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 30
# endif

typedef enum	e_filetype
{
	OUTFILE = 1,
	INFILE,
	NOT_FILE
}	t_filetype;

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct	s_cmd
{
	char		*cmd;
	char		**args;
	t_filetype	filetype;
	t_cmd		*next;
}	t_cmd;

typedef struct	s_token
{
	int				expand;
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct	s_shell
{
	char	**env;
}	t_shell;

typedef struct	s_builtin
{
	char	*name;
	int		(*f)(char **args, t_shell *shell);
}	t_builtin;

void	init_signals(void);

// ENV FUNCTION

char	**copy_env(char **envp);
char	*get_env_value(char **env, char *name);
void	set_env_value(char **env, char *name, char *new_val);
int		len_name(char *args);

// BUILT-IN

int	exec_cd(char **args, t_shell *shell);
int	exec_export(char **args, t_shell *shell);
int	exec_unset(char **args, t_shell *shell);

extern int	g_value_exit;
// sig_handler.c
void	init_signals(void);

// token_utils.c
t_token	*ft_new_token(char *value, t_token_type type, int expand);
t_token	*ft_last_token(t_token *lst);
void	ft_add_token_back(t_token **lst, t_token *new);
void	ft_delete_front_token(t_token **stack);

//cmds_utils.c
t_cmd	*ft_last_cmd(t_cmd *lst);
void	add_cmd(t_cmd **lst, t_cmd *new);

// ????????
char	*ft_strjoin_free(char *s1, char const *s2);
// token.c
t_token *lexer(char *line);

// token_utils.c
void	print_token(t_token *tokens);

#endif
