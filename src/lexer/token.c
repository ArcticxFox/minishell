/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:43:46 by ejones            #+#    #+#             */
/*   Updated: 2026/06/25 18:45:28 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_word(char *str, int *i)
{
	int		start;
	char	*word;

	start = *i;
	word = NULL;
	if (str[*i] == '\'')
		word = extract_single_quotes(str, i);
	else if (str[*i] == '"')
		word = extract_double_quotes(str, i);
	else
	{
		while (str[*i] && !ft_is_whitespace(str[*i])
			&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>'
			&& str[*i] != '"' && str[*i] != '\'')
			++(*i);
		word = ft_substr(str, start, *i - start);
		if (ft_is_whitespace(str[(*i)]))
			word = ft_strjoin_free(word, " ");
	}
	if (!word)
		return (NULL);
	return (word);
}

int	check_special_char(t_token **token, char *s, int *i)
{
	if (s[*i] == '|')
		*token = ft_new_token(ft_strdup("|"), TOKEN_PIPE, 0);
	else if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
		{
			++(*i);
			*token = ft_new_token(ft_strdup(">>"), TOKEN_APPEND, 0);
		}
		else
			*token = ft_new_token(ft_strdup(">"), TOKEN_REDIR_OUT, 0);
	}
	else if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
		{
			++(*i);
			*token = ft_new_token(ft_strdup("<<"), TOKEN_HEREDOC, 0);
		}
		else
			*token = ft_new_token(ft_strdup("<"), TOKEN_REDIR_IN, 0);
	}
	else
		return (0);
	return (1);
}

int	add_token(t_token **tokens, char *line, int *i)
{
	t_token	*token;
	char	*str;

	token = NULL;
	str = NULL;
	if (check_special_char(&token, line, i))
	{
		if (!token)
			exit(0);
		ft_add_token_back(tokens, token);
		++(*i);
	}
	else
	{
		str = extract_word(line, i);
		if (!str)
		{
			ft_printf("syntax error\n");
			while (*tokens)
				ft_delete_front_token(tokens);
			return (EXIT_FAILURE);
		}
		ft_add_token_back(tokens, ft_new_token(str, TOKEN_WORD, 1));
	}
	return (EXIT_SUCCESS);
}

t_token	*lexer(char *line)
{
	int		i;
	// char	*str;
	t_token	*tokens;

	i = 0;
	// str = NULL;
	tokens = NULL;
	while (line[i])
	{
		skip_whitespaces(line, &i);
		if (!line[i])
			break ;
		if (add_token(&tokens, line, &i))
			return (NULL);
	}
	return (tokens);
}
