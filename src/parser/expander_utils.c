/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:59:52 by ejones            #+#    #+#             */
/*   Updated: 2026/07/09 19:53:27 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_word(char *str, int *i, bool *space)
{
	int		start;
	char	*word;

	start = *i;
	word = NULL;
	if (str[*i] == '\'')
		word = extract_single_quotes(str, i, space);
	else if (str[*i] == '"')
		word = extract_double_quotes(str, i, space);
	else
	{
		while (str[*i] && !ft_is_whitespace(str[*i])
			&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>'
			&& str[*i] != '"' && str[*i] != '\'')
			++(*i);
		word = ft_substr(str, start, *i - start);
		if (ft_is_whitespace(str[(*i)]))
			*space = true;
	}
	if (!word)
		return (NULL);
	return (word);
}

t_token	*tmp_lexer(char *line, t_shell *shell)
{
	int		i;
	int		error;
	t_token	*tokens;

	i = 0;
	error = 0;
	tokens = NULL;
	while (line[i] && error == 0)
	{
		skip_whitespaces(line, &i);
		if (!line[i])
			break ;
		if (add_token(&tokens, line, &i, shell))
			error = -2;
	}
}
