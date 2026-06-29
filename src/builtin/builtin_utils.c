/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:03:25 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/29 13:06:46 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exit(t_shell *shell, int status)
{
	while (shell->head)
		ft_delete_front_cmd(&shell->head);
	free_memory(shell->env);
	exit(status);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_overflowed(char *str)
{
	static const char	*max = "9223372036854775807";
	static const char	*min_abs = "9223372036854775808";
	const char			*limit;
	int					i;
	int					len;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		limit = (str[i++] == '-') ? min_abs : max;
	}
	else
		limit = max;
	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	return (ft_strncmp(str + i, limit, 19) > 0);
}

long long	ft_atoll(char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + (str[i++] - '0');
	return (result * sign);
}
