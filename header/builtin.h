/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:15:14 by ejones            #+#    #+#             */
/*   Updated: 2026/07/03 13:47:37 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structs.h"

int			builtin(char **args, t_shell *shell);
int			is_builtin(char *cmd);
int			is_numeric(char *str);
int			is_overflowed(char *str);
long long	ft_atoll(char *str);

int			exec_cd(char **args, t_shell *shell);
int			exec_export(char **args, t_shell *shell);
int			exec_unset(char **args, t_shell *shell);
int			exec_env(char **args, t_shell *shell);

#endif
