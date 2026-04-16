/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:12:56 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:57:47 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = 0;
	if (lendst >= size)
		return (size + lensrc);
	while (*(src + i) && i < size - lendst - 1)
	{
		*(dst + lendst + i) = *(src + i);
		i++;
	}
	*(dst + lendst + i) = '\0';
	return (lendst + lensrc);
}
