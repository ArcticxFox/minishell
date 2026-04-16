/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbrbase_fd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:04:41 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:58:25 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_putnbrbase_fd(unsigned int n, char *base, int fd)
{
	unsigned int	base_size;
	int				counte;

	base_size = ft_strlen(base);
	counte = 0;
	if (n < base_size)
		counte += ft_printf_putchar_fd(base[n % base_size], fd);
	else if (n > 9)
	{
		counte += ft_putnbrbase_fd(n / base_size, base, fd);
		counte += ft_printf_putchar_fd(base[n % base_size], fd);
	}
	return (counte);
}

int	ft_putnbrbase_x(va_list args)
{
	unsigned int	u;

	u = va_arg(args, unsigned);
	u = ft_putnbrbase_fd(u, "0123456789abcdef", 1);
	return (u);
}

int	ft_putnbrbase_uppercase(va_list args)
{
	unsigned int	u;

	u = va_arg(args, unsigned);
	u = ft_putnbrbase_fd(u, "0123456789ABCDEF", 1);
	return (u);
}
