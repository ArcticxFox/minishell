/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:14:32 by ejones            #+#    #+#             */
/*   Updated: 2026/07/05 14:23:53 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "structs.h"

//token.c
t_token	*lexer(char *line, t_shell *shell);
int		check_special_char(t_token **token, char *s, int *i);
char	*extract_word(char *str, int *i, bool *space);
char	*assemble_words(char *str, int *i, bool *space);

//token_add.c
int		add_token_word(t_token **tokens, char *line, int *i, t_shell *shell);
int		add_token(t_token **tokens, char *line, int *i, t_shell *shell);

//token_util2.c
int		ft_is_whitespace(char c);
void	skip_whitespaces(char *line, int *i);
char	*extract_single_quotes(char *str, int *i, bool *space);
char	*extract_double_quotes(char *str, int *i, bool *space);

t_token	*ft_new_token(char *value, t_tk_type type, int expand, bool space);
t_token	*ft_last_token(t_token *lst);
void	ft_add_token_back(t_token **lst, t_token *new);
void	ft_delete_front_token(t_token **stack);

//syntax_errors.c
bool	check_for_syntax_error(t_token *tokens);

#endif
