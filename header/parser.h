/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:14:55 by ejones            #+#    #+#             */
/*   Updated: 2026/05/10 19:19:07 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

t_cmd	*get_commands(t_token *tokens);

t_cmd	*ft_last_cmd(t_cmd *lst);
void	add_cmd(t_cmd **lst, t_cmd *new_cmd);

void	print_token(t_token *tokens);
void	print_commands(t_cmd *cmd);

#endif
