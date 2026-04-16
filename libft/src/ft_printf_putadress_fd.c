/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putadress_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:24:54 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:58:08 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_putadress_fd(unsigned long int n, int fd)
{
	char		*base;
	int			counte;

	base = "0123456789abcdef";
	counte = 0;
	if (n < 16)
		counte += ft_printf_putchar_fd(base[n % 16], fd);
	else if (n > 9)
	{
		counte += ft_putadress_fd(n / 16, fd);
		counte += ft_printf_putchar_fd(base[n % 16], fd);
	}
	return (counte);
}

int	ft_putadress(va_list args)
{
	void	*u;
	int		count;

	u = va_arg(args, void *);
	count = 0;
	if (!u)
		count = ft_printf_putstr_fd("(nil)", 1);
	else
	{
		count += ft_printf_putstr_fd("0x", 1);
		count += ft_putadress_fd((unsigned long)u, 1);
	}
	return (count);
}
