/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:35:30 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:57:47 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;

	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (dest <= src)
	{
		cdest = (unsigned char *) ft_memcpy(cdest, csrc, n);
	}
	else if (dest > src)
	{
		cdest = cdest + n - 1;
		csrc = csrc + n - 1;
		while (n--)
		{
			*cdest-- = *csrc--;
		}
	}
	return (dest);
}
