/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:59:50 by ejones            #+#    #+#             */
/*   Updated: 2026/04/28 17:08:15 by ejones           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/header/libft.h"

// typedef enum	e_quotes
// {
// 	NO_QUOTES,
// 	SINGLE_QUOTE,
// 	DOUBLE_QUOTES
// }	t_quotes;

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
	char	*cmd;
	char	**args;
	t_cmd	*next;
}	t_cmd;

typedef struct	s_token
{
	int				expand;
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

extern int	g_value_exit;
// sig_handler.c
void	init_signals(void);

// token_utils.c
t_token	*ft_new_token(char *value, t_token_type type, int expand);
t_token	*ft_last_token(t_token *lst);
void	ft_add_token_back(t_token **lst, t_token *new);
void	ft_delete_front_token(t_token **stack);

// ????????
char	*ft_strjoin_free(char *s1, char const *s2);
// token.c
t_token *lexer(char *line);

// token_utils.c
void	print_token(t_token *tokens);


#endif
