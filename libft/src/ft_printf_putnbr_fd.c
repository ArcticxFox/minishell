/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:30:14 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:59:12 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_printf_putnbr_fd(int n, int fd)
{
	int	counte;

	counte = 0;
	if (-2147483648 == n)
	{
		counte = ft_printf_putstr_fd("-2147483648", fd);
		return (counte);
	}
	else if (n < 0)
	{
		counte += ft_printf_putchar_fd('-', fd);
		n *= -1;
		counte += ft_printf_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		counte += ft_printf_putnbr_fd(n / 10, fd);
		counte += ft_printf_putnbr_fd(n % 10, fd);
	}
	else
		counte += ft_printf_putchar_fd(n + '0', fd);
	return (counte);
}

int	ft_putnbr(va_list args)
{
	int	u;

	u = va_arg(args, int);
	u = ft_printf_putnbr_fd(u, 1);
	return (u);
}
