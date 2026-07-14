/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 19:07:01 by ejones            #+#    #+#             */
/*   Updated: 2026/07/14 15:15:32 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expand_arg(t_shell *shell, t_token **tokens)
{
	int		current;
	char	**tab;

	current = 0;
	tab = NULL;
	tab = ft_calloc(2, sizeof(char *));
	tab[0] = ft_strdup("\0");
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if (!find_token_words(tokens))
		{
			if (current > 0)
			{
				free(tab[current]);
				tab[current] = NULL;
			}
			return (tab);
		}
		tab = expand_token(shell, (*tokens), tab, &current);
		(*tokens) = (*tokens)->next;
		if ((*tokens) && (*tokens)->type != TOKEN_PIPE)
		{
			tab = add_arg(tab, ft_strdup(""));
			current++;
		}
	}
	return (tab);
}

char	**get_args(t_shell *shell, t_token **tokens)
{
	char	**tab;

	tab = NULL;
	tab = expand_arg(shell, tokens);
	return (tab);
}
