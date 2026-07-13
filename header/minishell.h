/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:59:50 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 16:30:00 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/header/libft.h"

# include "structs.h"
# include "token.h"
# include "parser.h"
# include "builtin.h"
# include "env.h"
# include "signals.h"
# include "execute.h"
# include "pipe.h"

char	*expand(t_shell *shell, char *arg, t_tk_type type, int expand);
char	*ft_strjoin_free(char *s1, char const *s2);

char	*ft_env_name(t_shell *shell, char *str, int *i);
int		ft_get_env_len(t_shell *shell, char *name);
char	*expand_string(t_shell *shell, char *str, int len);

void	read_old_history(t_shell *shell);
void	append_hist(char **env, char *line);

#endif
