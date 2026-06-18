/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:59:50 by ejones            #+#    #+#             */
/*   Updated: 2026/06/18 16:03:00 by ejones           ###   ########.fr       */
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

extern int	g_value_exit;

char	*ft_strjoin_free(char *s1, char const *s2);
char	*expand(char **env, char *arg);

#endif
