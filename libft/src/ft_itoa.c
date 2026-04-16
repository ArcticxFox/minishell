/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:24:06 by ejones            #+#    #+#             */
/*   Updated: 2026/01/06 15:04:26 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	nbr_len(int n)
{
	int		i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*specialcase(int n)
{
	char	*tmp;

	if (n == -2147483648)
	{
		tmp = ft_strdup("-2147483648");
		return (tmp);
	}
	else if (n == 0)
	{
		tmp = ft_strdup("0");
		return (tmp);
	}
	return (NULL);
}

static char	*positiv_nbr(int n)
{
	int		size;
	char	*str;

	size = nbr_len(n) + 1;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	size--;
	while (size--)
	{
		str[size] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

static char	*negative_nbr(int n)
{
	int		size;
	char	*str;

	size = nbr_len(n) + 2;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size--;
	n *= -1;
	while (size-- > 0)
	{
		str[size] = n % 10 + '0';
		n /= 10;
	}
	str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*tmp;

	if (n == -2147483648 || n == 0)
	{
		tmp = specialcase(n);
		return (tmp);
	}
	if (n > 0)
	{
		tmp = positiv_nbr(n);
		return (tmp);
	}
	if (n < 0)
	{
		tmp = negative_nbr(n);
		return (tmp);
	}
	return (NULL);
}
