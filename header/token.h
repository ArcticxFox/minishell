/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:14:32 by ejones            #+#    #+#             */
/*   Updated: 2026/06/23 13:41:59 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structs.h"

//token_util2.c
int		ft_is_whitespace(char c);
void	skip_whitespaces(char *line, int *i);
char	*extract_single_quotes(char *str, int *i);
char	*extract_double_quotes(char *str, int *i);

t_token	*lexer(char *line);

t_token	*ft_new_token(char *value, t_tk_type type, int expand);
t_token	*ft_last_token(t_token *lst);
void	ft_add_token_back(t_token **lst, t_token *new);
void	ft_delete_front_token(t_token **stack);

#endif
