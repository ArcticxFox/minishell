/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:56:30 by ejones            #+#    #+#             */
/*   Updated: 2026/06/23 13:07:50 by ejones           ###   ########.fr       */
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
	{
		return (ft_strjoin_free(token, " "));
	}
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
