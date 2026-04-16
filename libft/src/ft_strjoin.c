/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:24:40 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:57:47 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_new_str;
	size_t	i;
	size_t	j;
	char	*newstr;

	size_new_str = 0;
	if (!s1 || !s2)
		return (NULL);
	size_new_str = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	j = 0;
	newstr = (char *)malloc(size_new_str * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (s1[j] && i < size_new_str - 1)
		newstr[i++] = s1[j++];
	j = 0;
	while (s2[j] && i < size_new_str - 1)
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}
