/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:12:33 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/22 13:38:35 by leonpouet        ###   ########.fr       */
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
int		count_cmds(t_cmd *cmds);
void	free_pipes(int **pipes, int i);
void	close_all_pipes(int **pipes, int n);
int		**create_pipes(int n);
void	child_pipe_setup(t_cmd *cmd, t_pipe_state *state, t_shell *shell);
int		apply_redirs(t_redir *redir);
void	execute_child(t_cmd *cmd, int fd_in, int fd_out, t_shell *shell);

#endif
