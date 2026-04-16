/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putchar_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:07:42 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:58:02 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_printf_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putchar(va_list args)
{
	char	c;

	c = va_arg(args, int);
	ft_printf_putchar_fd(c, 1);
	return (1);
}
