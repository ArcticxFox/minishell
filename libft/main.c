/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:57:58 by ejones            #+#    #+#             */
/*   Updated: 2026/07/07 18:40:24 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/libft.h"
#include "stdio.h"

int	main(void)
{
	char	*str;

	str = "42";
	printf("%d", ft_atoi(str));
	ft_printf("hello World %d", 42);
	return (0);
}
