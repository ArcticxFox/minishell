/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 00:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/24 00:00:00 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "structs.h"

void	execute_pipeline(t_cmd *list, t_shell *shell);
void	free_pipes(int **pipes, int i);
void	close_all_pipes(int **pipes, int n);
int		**create_pipes(int n);
void	child_pipe_setup(t_cmd *cmd, t_pipe_state *state, t_shell *shell);

#endif
