/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 18:27:48 by ejones            #+#    #+#             */
/*   Updated: 2026/05/19 18:07:13 by ejones           ###   ########.fr       */
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
	printf("%s\n", value);
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
			len += ft_get_env_len(env, name) - 1;
			printf("name = %s\nlenght = %d\n", name, len);
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
// void	expand(t_shell **shell)
// {
// 	int		i;
// 	int		len;
// 	char	*str;
// 	t_cmd	*tmp;

// 	i = 0;
// 	str = NULL;
// 	tmp = (*shell)->head;
// 	while (tmp->args[i])
// 	{
// 		if (check_for_dollar(tmp->args[i], &i))
// 		{

// 		}
// 		++i;
// 	}
// }



