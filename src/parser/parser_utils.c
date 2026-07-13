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

char	**add_arg(char **tab, char *str)
{
	int		i;
	int		len;
	char	**new;

	len = 0;
	while (tab[len])
		len++;
	new = ft_calloc(len + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = tab[i];
		i++;
	}
	new[len] = str;
	new[len + 1] = NULL;
	free(tab);
	return (new);
}

void	append_split_words(char ***tab, int *n, char *str)
{
	char	**words;
	int		i;

	words = get_expand_with_no_quotes(str, count_words(str));
	if (!words)
		return ;
	if (words[0])
		(*tab)[*n] = ft_strjoin_free((*tab)[*n], words[0]);
	i = 1;
	while (words[i])
	{
		*tab = add_arg(*tab, words[i]);
		++(*n);
		++i;
	}
	free(words[0]);
	free(words);
}

char	*trim_quotes(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	if (*str == '\'')
		tmp = ft_strtrim(str, "'");
	else if (*str == '\"')
		tmp = ft_strtrim(str, "\"");
	else
		tmp = ft_strdup(str);
	free(str);
	return (tmp);
}

char	**expand_token(t_shell *shell, t_token *token, char **tab, int *current)
{
	int		i;
	char	*piece;
	char	*expanded;

	i = 0;
	piece = NULL;
	expanded = NULL;
	while (token->value[i])
	{
		piece = extract_expand_type(token->value, &i);
		expanded = expand(shell, piece, token->type, 1);
		if (piece && *piece != '\"' && *piece != '\'')
			append_split_words(&tab, current, expanded);
		else
		{
			tab[*current] = ft_strjoin_free(tab[*current], expanded);
		}
		free(piece);
		free(expanded);
	}
	return (tab);
}

char	**expand_arg(t_shell *shell, t_token **tokens)
{
	int		current;
	char	**tab;

	current = 0;
	tab = NULL;
	tab = ft_calloc(2, sizeof(char *));
	tab[0] = ft_strdup("\0");
	while (*tokens && (*tokens)->type == TOKEN_WORD)
	{
		if (!find_token_words(tokens))
		{
			free_memory(tab);
			return (NULL);
		}
		tab = expand_token(shell, (*tokens), tab, &current);
		(*tokens) = (*tokens)->next;
		if ((*tokens) && (*tokens)->type == TOKEN_WORD)
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
