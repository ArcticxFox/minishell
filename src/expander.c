/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:27:48 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 17:27:56 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_get_lenght(t_shell *shell, char *str)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	len = 0;
	name = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$')
		{
			++i;
			name = ft_env_name(shell, str, &i);
			len += ft_get_env_len(shell, name);
			free(name);
		}
		else
		{
			++i;
			++len;
		}
	}
	return (len);
}

bool	check_for_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		++i;
	}
	return (false);
}

char	*expand(t_shell *shell, char *arg, t_tk_type type, int expand)
{
	int		len;
	char	*str;

	str = NULL;
	(void)expand;
	if (*arg != '\'' && check_for_dollar(arg) && type != TOKEN_HEREDOC)
	{
		len = ft_get_lenght(shell, arg);
		str = expand_string(shell, arg, len);
	}
	else
	{
		str = ft_strdup(arg);
	}
	str = trim_quotes(str);
	return (str);
}
