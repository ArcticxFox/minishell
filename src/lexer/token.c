/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:43:46 by ejones            #+#    #+#             */
/*   Updated: 2026/07/07 16:08:20 by ejones           ###   ########.fr       */
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

int	check_special_char(t_token **token, char *s, int *i)
{
	if (s[*i] == '|')
		*token = ft_new_token(ft_strdup("|"), TOKEN_PIPE, 0, false);
	else if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
		{
			++(*i);
			*token = ft_new_token(ft_strdup(">>"), TOKEN_APPEND, 0, false);
		}
		else
			*token = ft_new_token(ft_strdup(">"), TOKEN_REDIR_OUT, 0, false);
	}
	else if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
		{
			++(*i);
			*token = ft_new_token(ft_strdup("<<"), TOKEN_HEREDOC, 0, false);
		}
		else
			*token = ft_new_token(ft_strdup("<"), TOKEN_REDIR_IN, 0, false);
	}
	else
		return (0);
	return (1);
}

int	add_token_word(t_token **tokens, char *line, int *i)
{
	bool	space;
	char	*str;

	space = false;
	str = NULL;
	str = extract_word(line, i, &space);
	if (!str)
	{
		g_value_exit = 2;
		while (*tokens)
			ft_delete_front_token(tokens);
		return (EXIT_FAILURE);
	}
	ft_add_token_back(tokens, ft_new_token(str, TOKEN_WORD, 1, space));
	return (EXIT_SUCCESS);
}

int	add_token(t_token **tokens, char *line, int *i)
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
		add_token_word(tokens, line, i);
	}
	return (EXIT_SUCCESS);
}

t_token	*lexer(char *line)
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
		if (add_token(&tokens, line, &i))
			error = -2;
	}
	// if (error == -2 || check_for_syntax_error(tokens))
	// {
	// 	g_value_exit = 2;
	// 	while (tokens)
	// 		ft_delete_front_token(&tokens);
	// 	return (NULL);
	// }
	return (tokens);
}
