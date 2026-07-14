/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 19:07:01 by ejones            #+#    #+#             */
/*   Updated: 2026/07/14 15:24:12 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (words[i] && words[i][0] != '\0')
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

char	**expand_token(t_shell *shell, t_token *token, char **tab,
			int *current)
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
