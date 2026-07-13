/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:20:33 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 19:07:01 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_arg(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && !ft_is_whitespace(str[i]))
		++i;
	return (i);
}

char	*extract_expand_type(char *str, int *i)
{
	int		start;
	char	*word;

	start = *i;
	word = NULL;
	if (str[*i] == '\'')
		word = extract_single_quotes(str, i, NULL);
	else if (str[*i] == '"')
		word = extract_double_quotes(str, i, NULL);
	else
	{
		while (str[*i] && !ft_is_whitespace(str[*i])
			&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>'
			&& str[*i] != '"' && str[*i] != '\'')
			++(*i);
		word = ft_substr(str, start, *i - start);
	}
	if (!word)
		return (NULL);
	return (word);
}

int	count_words(char *arg)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (arg[i])
	{
		if (arg[i] && !ft_is_whitespace(arg[i]))
		{
			++n;
			while (arg[i] && !ft_is_whitespace(arg[i]))
				++i;
		}
		else
			++i;
	}
	return (n);
}

char	**get_expand_with_no_quotes(char *str, int n)
{
	int		i;
	int		j;
	char	**args;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	args = ft_calloc(n + 1, sizeof(char *));
	if (args == NULL)
		return (NULL);
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
		{
			args[j] = ft_substr(str, i, len_arg(&str[i]));
			if (!args[j++])
				return (free_memory(args));
			i += len_arg(&str[i]);
		}
		else
			++i;
	}
	return (args);
}

bool	find_token_words(t_token **tokens)
{
	while (*tokens && ft_isspecial(*tokens) == 2)
	{
		if (ft_isspecial(*tokens) == 2 && (*tokens)->next)
			*tokens = (*tokens)->next->next;
		else
			(*tokens) = (*tokens)->next;
	}
	if (!(*tokens) || ft_isspecial(*tokens) == 1)
		return (false);
	return (true);
}
