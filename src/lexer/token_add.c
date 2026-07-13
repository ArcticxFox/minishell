/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 19:07:01 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 19:07:01 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token_word(t_token **tokens, char *line, int *i, t_shell *shell)
{
	bool	space;
	char	*str;

	space = false;
	str = NULL;
	str = assemble_words(line, i, &space);
	if (!str)
	{
		shell->exit_value = 2;
		while (*tokens)
			ft_delete_front_token(tokens);
		return (EXIT_FAILURE);
	}
	ft_add_token_back(tokens, ft_new_token(str, TOKEN_WORD, 1, space));
	return (EXIT_SUCCESS);
}

int	add_token(t_token **tokens, char *line, int *i, t_shell *shell)
{
	t_token	*token;

	token = NULL;
	if (check_special_char(&token, line, i))
	{
		if (!token)
			exit(0);
		ft_add_token_back(tokens, token);
		++(*i);
	}
	else
	{
		add_token_word(tokens, line, i, shell);
	}
	return (EXIT_SUCCESS);
}
