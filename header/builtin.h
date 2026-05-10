/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:15:14 by ejones            #+#    #+#             */
/*   Updated: 2026/05/10 19:15:20 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structs.h"

int		builtin(char **args, t_shell *shell);

int		exec_cd(char **args, t_shell *shell);
int		exec_export(char **args, t_shell *shell);
int		exec_unset(char **args, t_shell *shell);

void	free_all(t_shell *shell, char **cmd_args,
			char *str, int n);

#endif
