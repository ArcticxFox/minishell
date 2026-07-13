/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:43:46 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 19:06:05 by ejones           ###   ########.fr       */
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

char	*assemble_words(char *str, int *i, bool *space)
{
	char	*s1;
	char	*s2;

	s1 = extract_word(str, i, space);
	while (str[*i] && !ft_is_whitespace(str[*i])
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
	{
		if (s1)
			s2 = extract_word(str, i, space);
		if (!s2)
		{
			free(s1);
			return (NULL);
		}
		s1 = ft_strjoin_free(s1, s2);
		free(s2);
	}
	return (s1);
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

t_token	*lexer(char *line, t_shell *shell)
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
	if (error == -2 || check_for_syntax_error(tokens))
	{
		shell->exit_value = 2;
		while (tokens)
			ft_delete_front_token(&tokens);
		return (NULL);
	}
	return (tokens);
}
