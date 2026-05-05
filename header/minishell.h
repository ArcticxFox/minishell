/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:59:50 by ejones            #+#    #+#             */
/*   Updated: 2026/05/05 11:59:30 by leonpouet        ###   ########.fr       */
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

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct	s_token
{
	char			*str;
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

#endif
