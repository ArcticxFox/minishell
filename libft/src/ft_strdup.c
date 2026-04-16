/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:12:57 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:57:47 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	int		i;
	char	*dup;

	size = ft_strlen(s) + 1;
	i = 0;
	dup = (char *)malloc(size * sizeof(char));
	if (dup == NULL)
		return (0);
	while (i < size - 1)
	{
		dup[i] = ((char *)s)[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
