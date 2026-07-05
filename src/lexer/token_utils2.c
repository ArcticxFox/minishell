/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:56:30 by ejones            #+#    #+#             */
/*   Updated: 2026/07/05 14:34:44 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void	skip_whitespaces(char *line, int *i)
{
	while (line[*i] && ft_is_whitespace(line[*i]))
		++(*i);
}

char	*extract_single_quotes(char *str, int *i, bool *space)
{
	int		start;
	char	*token;

	start = (*i)++;
	while (str[*i] && str[*i] != '\'')
		++(*i);
	if (str[*i] != '\'')
	{
		ft_printf("unexpected EOF file while looking for matching `\''\n");
		ft_printf("minishell: syntax error\n");
		return (NULL);
	}
	++(*i);
	token = ft_substr(str, start, *i - start);
	if (!token || (*i - start) <= 1)
		return (NULL);
	if (ft_is_whitespace(str[(*i)]))
	{
		*space = true;
		return (token);
	}
	if (!token)
		return (NULL);
	return (token);
}

char	*extract_double_quotes(char *str, int *i, bool *space)
{
	int		start;
	char	*token;

	start = (*i)++;
	while (str[*i] && str[*i] != '"')
		++(*i);
	if (str[*i] != '"')
	{
		ft_printf("unexpected EOF file while looking for matching `\"'\n");
		ft_printf("minishell: syntax error\n");
		return (NULL);
	}
	++(*i);
	token = ft_substr(str, start, *i - start);
	if (!token || (*i - start) <= 1)
		return (NULL);
	if (ft_is_whitespace(str[(*i)]))
	{
		*space = true;
		return (ft_strjoin_free(token, " "));
	}
	if (!token)
		return (NULL);
	return (token);
}
