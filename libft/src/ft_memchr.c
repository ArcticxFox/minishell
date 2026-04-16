/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:23:47 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:57:47 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*is_chr_find;

	p = (unsigned char *)s;
	is_chr_find = NULL;
	while (n--)
	{
		if (*p != (unsigned char)c)
		{
			p++;
		}
		else
		{
			is_chr_find = p;
			break ;
		}
	}
	return (is_chr_find);
}
