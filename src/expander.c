/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:27:48 by ejones            #+#    #+#             */
/*   Updated: 2026/06/02 13:57:28 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	*ft_realloc(void *ptr, size_t size)
{
	void	*tmp;

	if (size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	tmp = ft_calloc(1, size);
	if(!tmp)
		return (NULL);
	tmp = ft_memcpy(tmp, ptr, size - 1);
	free(ptr);
	return (tmp);
}

char	*ft_env_name(char *str, int *i)
{
	int		len;
	int		start;
	char	*name;

	len = 0;
	start = *i;
	name = NULL;
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
	len = ft_strlen(value);
	return (len);
}

int	ft_get_lenght(char **env, char *str)
{
	int		i;
	int		len;
	char	*name;
	char	*env_v;

	i = 0;
	len = 0;
	name = NULL;
	env_v = NULL;
	while (str[i])
	{
		if (str[i] == '$')
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

	name = ft_env_name(str, i);
	env_v = get_env_value(env, name);

	n = ft_strlcpy(new_str, env_v, ft_strlen(env_v) + 1);
	if (n == 0)
		new_str = NULL;
	free(name);
	return (n);
}

char	*expand_string(char **env, char *str)
{
	int		i;
	int		n;
	int		len;
	char	*new_str;

	i = 0;
	n = 0;
	len = ft_get_lenght(env, str);
	new_str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			++i;
			n += ft_copy_into_env(env, str, &new_str[n], &i);
		}
		else
		{
			new_str[n] = str[i];
			++n;
			++i;
		}
	}
	free(str);
	new_str[len] = '\0';
	printf("new_str: %s\n", new_str);
	return (new_str);
}

void	expand(t_shell *shell)
{
	int		i;
	char	*str;
	t_cmd	*tmp;

	i = 0;
	str = NULL;
	tmp = shell->head;
	while (tmp->args[i])
	{
		if (check_for_dollar(tmp->args[i]))
		{
			tmp->args[i] = expand_string(shell->env, tmp->args[i]);
		}
		++i;
	}
}



