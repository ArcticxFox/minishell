/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:06:37 by ejones            #+#    #+#             */
/*   Updated: 2026/04/30 16:25:55 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	*free_memory(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

// COunts the number of sings
static int	str_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	nbr_splits(const char *s, char c)
{
	int	i;
	int	words_count;

	i = 0;
	words_count = 0;
	while (s != NULL && s[i])
	{
		if (s[i] != c)
		{
			words_count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (words_count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	split = (char **)ft_calloc(nbr_splits(s, c) + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j] = ft_substr(s, i, str_len(&s[i], c));
			if (split[j++] == NULL)
				return (free_memory(split));
			i += str_len(&s[i], c);
		}
		else
			i++;
	}
	return (split);
}
