/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:14:55 by ejones            #+#    #+#             */
/*   Updated: 2026/06/18 11:34:37 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

// t_cmd	*get_commands(t_token *tokens);

void	add_cmd(t_cmd **lst, t_cmd *new_cmd);
void	ft_delete_front_cmd(t_cmd **stack);

void	print_token(t_token *tokens);
void	print_commands(t_cmd *cmd);

// t_cmd	*tmp_get_commands(t_token *tokens);
t_cmd	*tmp_get_commands(t_token *tokens, char **env);
void	ft_delete_front_redir(t_redir **stack);
void	ft_add_back_redir(t_redir **lst, t_redir *new_cmd);

#endif
