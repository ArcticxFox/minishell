/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:27:48 by ejones            #+#    #+#             */
/*   Updated: 2026/06/02 16:37:34 by leonpouet        ###   ########.fr       */
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
	// int		len;
	int		start;
	char	*name;

	// len = 0;
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
	// char	*env_v;

	i = 0;
	len = 0;
	name = NULL;
	// env_v = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			++i;
			name = ft_env_name(str, &i);
			len += ft_get_env_len(env, name) - 1;
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

// char	*ft_copy_into_env()
// {}

void	expand_string(char **env, char *str)
{
	int		i;
	int		len;
	char	*name;
	char	*env_v;

	i = 0;
	len = ft_get_lenght(env, str);
	name = NULL;
	env_v = NULL;
	str = ft_realloc(str, (sizeof(char) * len) + 1);
	if (!str)
		return ;
	while (i < len)
	{
		if (str[i] == '$')
		{
			++i;
			name = ft_env_name(str, &i);
			i -= ft_strlen(name) + 1;
			env_v = get_env_value(env, name);
			i += (int)ft_strlcpy(&str[i], env_v, ft_strlen(env_v)) - 1;
			free(name);
			name = NULL;
		}
		else
		{
			++i;
		}
	}
	printf("\nstr = %s\n", str);
}

void	expand(t_shell *shell)
{
	int		i;
	// char	*str;
	t_cmd	*tmp;

	i = 0;
	// str = NULL;
	tmp = shell->head;
	while (tmp->args[i])
	{
		if (check_for_dollar(tmp->args[i]))
		{
			expand_string(shell->env, tmp->args[i]);
		}
		++i;
	}
}



