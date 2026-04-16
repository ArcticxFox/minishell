/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:26:12 by ejones            #+#    #+#             */
/*   Updated: 2026/01/06 15:03:14 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/../header/libft.h"

int	ft_atoi(const char *nptr)
{
	long	res;
	int		i;

	res = 0;
	i = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
	{
		nptr++;
	}
	if ((*nptr == '+' || *nptr == '-'))
	{
		if (*nptr == '-')
			i *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (res < -2147483648 || res > 2147483647)
			return (-2);
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return (res * i);
}
