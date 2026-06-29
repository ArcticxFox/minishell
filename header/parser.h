/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:14:55 by ejones            #+#    #+#             */
/*   Updated: 2026/06/25 16:53:49 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

//get_cmds.c
t_cmd	*get_commands(t_token *tokens, char **env);
char	**get_args(t_token **tokens, char **env);

//parseur_utils.c
void	add_cmd(t_cmd **lst, t_cmd *new_cmd);
void	ft_add_back_redir(t_redir **lst, t_redir *new_cmd);

//print_structs.c
void	print_token(t_token *tokens);
void	print_commands(t_cmd *cmd);

// utils.c
int		ft_isspecial(t_token *token);
int		count_args(t_token *tokens);
void	ft_delete_front_redir(t_redir **stack);
void	ft_delete_front_cmd(t_cmd **stack);
t_redir	*new_redir(t_token *tokens, char **env);

#endif
