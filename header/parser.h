/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:14:55 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 16:51:11 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
//get_cmds.c
t_cmd	*get_commands(t_shell *shell, t_token *tokens);

//print_structs.c
void	print_token(t_token *tokens);
void	print_commands(t_cmd *cmd);

//cmd_linked_lst.c
void	add_cmd(t_cmd **lst, t_cmd *new_cmd);
void	ft_delete_cmd(t_cmd **stack);

//redir_parser.c
int		ft_isspecial(t_token *token);
void	ft_add_back_redir(t_redir **lst, t_redir *new_cmd);
void	ft_delete_front_redir(t_redir **stack);
t_redir	*new_redir(t_shell *shell, t_token *tokens);

// parser_utils.c
char	**get_args(t_shell *shell, t_token **tokens);
char	*trim_quotes(char *str);


char	**expand_token(t_shell *shell, t_token *token, char **tab, int *current);

#endif
