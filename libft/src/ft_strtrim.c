/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:48:55 by enones            #+#    #+#             */
/*   Updated: 2026/01/02 13:57:47 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
// return 0 if the chr not found
static int	check_chr(char c, char *set)
{
	int	n;

	n = 0;
	while (set[n])
	{
		if (c == set[n])
			break ;
		n++;
	}
	if (set[n] != '\0')
		return (1);
	return (0);
}

// Return leght of trim and Backspace unwanted chr
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*set_tmp;
	char	*trim;

	if (!set)
		set_tmp = "";
	else
		set_tmp = (char *)set;
	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (check_chr(s1[end - 1], (char *)set_tmp) && end)
		end--;
	while (check_chr(s1[start], (char *)set_tmp) && s1[start])
		start++;
	trim = ft_substr(s1, start, end - start);
	if (!trim)
		return (NULL);
	return (trim);
}
