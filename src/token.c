/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:43:46 by ejones            #+#    #+#             */
/*   Updated: 2026/04/30 16:59:12 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);

}

void	skip_whitespaces(char *line, int *i)
{
	while(line[*i] && ft_is_whitespace(line[*i]))
		++(*i);
}

char	*extract_single_quotes(char *str, int *i)
{
	int		start;
	char	*token;

	start = *i;
	if (str[*i] == '\'')
		++(*i);
	while (str[*i] && str[*i] != '\'')
		++(*i);
	if (str[*i] == '\'')
		++(*i);
	if ((*i - start) <= 1)
		return (NULL);
	token = ft_substr(str, start, *i - start);
	if (!token)
		return (NULL);
	if (ft_is_whitespace(str[(*i)]))
		return (ft_strjoin_free(token, " "));
	if (!token)
		return (NULL);
	return (token);
}

char	*extract_double_quotes(char *str, int *i)
{
	int		start;
	char	*token;

	start = *i;
	if (str[*i] == '"')
		++(*i);
	while (str[*i] && str[*i] != '"')
		++(*i);
	if (str[*i] == '"')
		++(*i);
	if ((*i - start) <= 1)
		return (NULL);
	token = ft_substr(str, start, *i - start);
	if (!token || (*i - start) <= 1)
		return (NULL);
	if (ft_is_whitespace(str[(*i)]))
		return (ft_strjoin_free(token, " "));
	if (!token)
		return (NULL);
	return (token);
}

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
		while(str[*i] && !ft_is_whitespace(str[*i])
			&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>' && str[*i] != '"' && str[*i] != '\'')
			++(*i);
		word = ft_substr(str, start, *i - start);
	}
	if (!word)
		return(NULL);
	return (word);
}

int	check_special_char(t_token **token, char *s, int *i)
{
	if (s[*i] == '|')
		*token = ft_new_token("|", TOKEN_PIPE, 0);
	else if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
		{
			++(*i);
			*token = ft_new_token(">>", TOKEN_APPEND, 0);
		}
		else
			*token = ft_new_token(">", TOKEN_REDIR_OUT, 0);
	}
	else if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
		{
			++(*i);
			*token = ft_new_token("<<", TOKEN_HEREDOC, 0);
		}
		else
			*token = ft_new_token("<", TOKEN_REDIR_IN, 0);
	}
	else
		return (0);
	return (1);
}

t_token *lexer(char *line)
{
	int		i = 0;
	char	*str;
	t_token	*token = NULL;
	t_token	*tokens = NULL;

	i = 0;
	str = NULL;
	token = NULL;
	tokens = NULL;
	while (line[i])
	{
		skip_whitespaces(line, &i);
		if (!line[i])
			break;
		if (check_special_char(&token, line, &i))
		{
			if (!token)
				exit(0);
			ft_add_token_back(&tokens, token);
			++i;
		}
		else
		{
			str = extract_word(line, &i);
			if (!str)
			{
				ft_printf("syntax error");
				while (tokens)
					ft_delete_front_token(&tokens);
				return (NULL);
			}
			ft_add_token_back(&tokens, ft_new_token(str, TOKEN_WORD, 1));
		}
	}
	print_token(tokens);
	return (tokens);
}
