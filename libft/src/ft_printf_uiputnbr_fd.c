/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uiputnbr_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:34:57 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:58:35 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	ft_uiputnbr_fd(unsigned int n, int fd)
{
	int	counte;

	counte = 0;
	if (n > 9)
		counte += ft_uiputnbr_fd(n / 10, fd);
	counte += ft_printf_putchar_fd(n % 10 + '0', fd);
	return (counte);
}

int	ft_uiputnbr(va_list args)
{
	unsigned int	u;

	u = va_arg(args, unsigned int);
	u = ft_uiputnbr_fd(u, 1);
	return (u);
}
