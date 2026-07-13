/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:27:48 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 13:57:55 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_env_name(char *str, int *i)
{
	int		start;
	char	*name;

	start = *i;
	name = NULL;
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		name = ft_substr(str, start, (*i) - start);
		if (!name)
			return (NULL);
		return (name);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start, (*i) - start);
	if (!name)
		return (NULL);
	return (name);
}

int	ft_get_env_len(char **env, char *name)
{
	int		len;
	char	*value;

	len = 0;
	if (!name)
		return (0);
	value = get_env_value(env, name);
	if (!value)
		return (0);
	len = ft_strlen(value);
	return (len);
}

int	ft_get_lenght(char **env, char *str)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	len = 0;
	name = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '$')
		{
			++i;
			name = ft_env_name(str, &i);
			len += ft_get_env_len(env, name);
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

int	ft_copy_into_env(char **env, char *str, char *new_str, int *i)
{
	int		n;
	char	*env_v;
	char	*name;

	n = 0;
	name = ft_env_name(str, i);
	env_v = get_env_value(env, name);
	free(name);
	if (!env_v)
		return (0);
	n = ft_strlcpy(new_str, env_v, ft_strlen(env_v) + 1);
	return (n);
}

char	*expand_string(char **env, char *str, int len)
{
	int		i;
	int		n;
	char	*new_str;

	i = 0;
	n = 0;
	new_str = malloc(len * sizeof(char) + 2);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '?' && str[i + 1] != '$')
		{
			++i;
			n += ft_copy_into_env(env, str, &new_str[n], &i);
		}
		else
		{
			if (str[i] == '$' && str[i + 1] == '$')
				++i;
			new_str[n++] = str[i++];
		}
	}
	new_str[len] = '\0';
	return (new_str);
}

char	*expand(char **env, char *arg, t_tk_type type, int expand)
{
	int		len;
	char	*str;

	str = NULL;
	(void)expand;
	if (*arg != '\'' && check_for_dollar(arg) && type != TOKEN_HEREDOC)
	{
		len = ft_get_lenght(env, arg);
		str = expand_string(env, arg, len);
	}
	else
	{
		str = ft_strdup(arg);
	}
	str = trim_quotes(str);
	return (str);
}
