/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:12:33 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/02 16:23:55 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "structs.h"

int	execute(t_cmd *list, t_shell *shell);
int	execute_single(t_cmd *list, t_shell *shell);
int	execute_pipeline(t_cmd *list, t_shell *shell);
int	execute_redir(t_cmd *list, t_shell *shell);

#endif
