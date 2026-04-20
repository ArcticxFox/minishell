/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:59:50 by ejones            #+#    #+#             */
/*   Updated: 2026/04/15 17:42:24 by ejones           ###   ########.fr       */
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

void init_signals(void);
t_token *ft_token_new(char *str, t_token_type token_type);
t_token *ft_token_last(t_token *lst);
void	ft_token_add_back(t_token **lst, t_token *new);
void	ft_token_delete_front(t_token **stack);
void	teste_token(void);


#endif
