/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:20:33 by ejones            #+#    #+#             */
/*   Updated: 2026/07/03 16:20:40 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *tokens)
{
	int	n;

	n = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (ft_isspecial(tokens) == 2 && tokens->next)
			tokens = tokens->next->next;
		else
		{
			++n;
			tokens = tokens->next;
		}
	}
	return (n);
}

char	*get_cmd_value(t_token **tokens, char **env)
{
	char	*value;

	value = NULL;
	while (*tokens && ft_isspecial(*tokens) == 2)
	{
		if (ft_isspecial(*tokens) == 2 && (*tokens)->next)
			*tokens = (*tokens)->next->next;
		else
			(*tokens) = (*tokens)->next;
	}
	if (!(*tokens) || ft_isspecial(*tokens) == 1)
		return (NULL);
	if ((*tokens)->value)
		value = expand(env, (*tokens)->value,
				(*tokens)->type, (*tokens)->expand);
	else
		value = NULL;
	(*tokens) = (*tokens)->next;
	return (value);
}

char	**get_args(t_token **tokens, char **env)
{
	int		n;
	int		i;
	char	**args;

	n = count_args(*tokens) + 1;
	i = 0;
	if (n < 1)
		return (NULL);
	args = malloc(sizeof(char *) * n);
	if (!args)
		return (NULL);
	while (i < n - 1)
	{
		args[i] = get_cmd_value(tokens, env);
		if (!args[i])
		{
			free_memory(args);
			return (NULL);
		}
		++i;
	}
	args[i] = NULL;
	return (args);
}

void	trim_files(t_redir **redir)
{
	t_redir	*tmp_redir;
	char	*tmp_file;

	tmp_redir = *redir;
	while (tmp_redir)
	{
		if (!(tmp_file = ft_strtrim(tmp_redir->file, " ")))
		{
			tmp_redir = tmp_redir->next;
			continue ;
		}
		free(tmp_redir->file);
		tmp_redir->file = tmp_file;
		if (tmp_redir->type == TOKEN_HEREDOC)
		{
			if (!(tmp_file = ft_strtrim(tmp_redir->file, " ")))
			{
				tmp_redir = tmp_redir->next;
				continue ;
			}
			free(tmp_redir->delimiter);
			tmp_redir->delimiter = tmp_file;
		}
		tmp_redir = tmp_redir->next;
	}
}

void	trim_args(char **args)
{
	int		i;
	char	*tmp;

	if (!args || !args[0])
		return ;
	i = 0;
	while (args[i])
	{
		tmp = ft_strtrim(args[i], " ");
		if (!tmp)
		{
			i++;
			continue ;
		}
		free(args[i]);
		args[i] = tmp;
		if (i == 0 && ft_strncmp(args[0], "echo", 6) == 0)
			while (args[i + 1])
				i++;
		else
			i++;
	}
	return ;
}
