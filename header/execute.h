/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:12:33 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/05 18:56:04 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"

void	execute(t_cmd *list, t_shell *shell);
int		setup_heredocs(t_cmd *head, char **env);
void	execute_child(t_cmd *cmd, int fd_in, int fd_out, t_shell *shell);
void	execute_single_builtin(t_cmd *cmd, t_shell *shell);
void	child_exit(t_shell *shell, int status);


char	*ft_strjoin_free(char *s1, char const *s2);
char	*get_path(char *cmd, t_shell *shell);
int		count_cmds(t_cmd *cmds);
int		apply_redirs(t_redir *redir);
int		handle_heredoc(t_redir *redir, char **env);
int		handle_file_redir(t_redir *redir);
void	read_heredoc_lines(int fd, t_redir *redir, char **env);

//execute_util_2.c
char	*expand_heredoc(char **env, char *line);
void	exit_status(t_pipe_state *state);

char	**get_args_for_execve(t_args *args);

#endif
