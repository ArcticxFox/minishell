/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:12:33 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/26 13:16:28 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"

void	execute(t_cmd *list, t_shell *shell);
void	execute_single(t_cmd *list, t_shell *shell);
void	execute_redir(t_cmd *list);
void	setup_heredocs(t_cmd *head);
void	execute_child(t_cmd *cmd, int fd_in, int fd_out, t_shell *shell);
void	execute_single_builtin(t_cmd *cmd, t_shell *shell);
void	child_exit(t_shell *shell, int status);

char	*get_path(char *cmd, t_shell *shell);

int		count_cmds(t_cmd *cmds);
int		apply_redirs(t_redir *redir);
int		handle_heredoc(t_redir *redir);

#endif
