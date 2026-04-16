/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:44:18 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 15:00:06 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

const t_flist	g_flist[] = {
{'d', ft_putnbr},
{'i', ft_putnbr},
{'u', ft_uiputnbr},
{'c', ft_putchar},
{'s', ft_putstr},
{'p', ft_putadress},
{'x', ft_putnbrbase_x},
{'X', ft_putnbrbase_uppercase},
{'\0', NULL}
};

static int	ft_print_args(va_list args, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (c == '%')
		count += ft_printf_putchar_fd('%', 1);
	else
	{
		while (g_flist[i].c != '\0')
		{
			if (g_flist[i].c == c)
				count += g_flist[i].f(args);
			if (c == '%')
				count += ft_printf_putchar_fd('%', 1);
			else
				i++;
		}
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	va_start(args, str);
	count = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_print_args(args, *str);
		}
		else
			count += ft_printf_putchar_fd(*str, 1);
		str++;
	}
	va_end(args);
	return (count);
}
