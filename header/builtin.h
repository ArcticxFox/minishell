/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:15:14 by ejones            #+#    #+#             */
/*   Updated: 2026/06/26 13:16:09 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structs.h"

int		builtin(char **args, t_shell *shell);
int		is_builtin(char *cmd);

int		exec_cd(char **args, t_shell *shell);
int		exec_export(char **args, t_shell *shell);
int		exec_unset(char **args, t_shell *shell);
int		exec_env(char **args, t_shell *shell);


#endif
