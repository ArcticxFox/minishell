/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:12:33 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/03 11:23:58 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"

void	execute(t_cmd *list, t_shell *shell);
void	execute_single(t_cmd *list, t_shell *shell);
void	execute_pipeline(t_cmd *list, t_shell *shell);
void	execute_redir(t_cmd *list);
char	*get_path(char *cmd, t_shell *shell);

#endif
