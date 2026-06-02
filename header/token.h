/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:14:32 by ejones            #+#    #+#             */
/*   Updated: 2026/05/15 17:13:03 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structs.h"

t_token	*lexer(char *line);

t_token	*ft_new_token(char *value, t_tk_type type, int expand);
t_token	*ft_last_token(t_token *lst);
void	ft_add_token_back(t_token **lst, t_token *new);
void	ft_delete_front_token(t_token **stack);

#endif
