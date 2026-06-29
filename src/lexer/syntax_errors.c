/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:03:05 by ejones            #+#    #+#             */
/*   Updated: 2026/06/29 20:46:27 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_error_near_newline(t_token *tokens)
{
	t_token	*last;
	t_token	*sec_last;

	last = ft_last_token(tokens);
	sec_last = tokens;
	if (!tokens->next)
	{
		if (last->type >= TOKEN_REDIR_IN && last->type <= TOKEN_HEREDOC)
		{
			ft_printf("minishel: syntax error near ");
			ft_printf("unexpected token 'newline'\n");
			return (true);
		}
		return (false);
	}
	while (sec_last->next != last)
		sec_last = sec_last->next;
	if (!(sec_last->type == TOKEN_WORD
			&& last->type >= TOKEN_PIPE && last->type <= TOKEN_HEREDOC))
		return (false);
	ft_printf("minishel: syntax error near unexpected token 'newline'\n");
	return (true);
}

bool	check_error_for_redir_or_pipe(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->next && tmp->type >= TOKEN_PIPE && tmp->type <= TOKEN_HEREDOC)
		{
			tmp = tmp->next;
			if (tmp->type == TOKEN_REDIR_IN)
				ft_printf("minishell: syntax error near unexpected token '<'");
			else if (tmp->type == TOKEN_REDIR_OUT)
				ft_printf("minishell: syntax error near unexpected token '>'");
			else if (tmp->type == TOKEN_APPEND)
				ft_printf("minishell: syntax error near unexpected token '>>'");
			else if (tmp->type == TOKEN_HEREDOC)
				ft_printf("minishell: syntax error near unexpected token '<<'");
			else if (tmp->type == TOKEN_PIPE)
				ft_printf("minishell: syntax error near unexpected token '|'");
			else
				continue;
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

bool	check_for_syntax_error(t_token *tokens)
{
	if (check_error_for_redir_or_pipe(tokens))
		return (true);
	if (check_error_near_newline(tokens))
		return (true);
	return (false);
}
