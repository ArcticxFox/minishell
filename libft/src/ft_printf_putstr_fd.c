/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:23:26 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:58:30 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_printf_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	write(fd, s, i);
	return (i);
}

int	ft_putstr(va_list args)
{
	char	*s;
	int		count;

	s = va_arg(args, char *);
	count = 0;
	if (!s)
		count += ft_printf_putstr_fd("(null)", 1);
	count += ft_printf_putstr_fd(s, 1);
	return (count);
}
