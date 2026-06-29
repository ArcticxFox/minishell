/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:38 by ejones            #+#    #+#             */
/*   Updated: 2026/06/29 16:24:26 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*find_redir(t_token *tokens, char **env)
{
	t_token	*tmp;
	t_redir	*redir;

	tmp = tokens;
	redir = NULL;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (ft_isspecial(tmp) == 2)
		{
			ft_add_back_redir(&redir, new_redir(tmp, env));
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (redir);
}
void	trim_files(t_redir **redir)
{
	t_redir	*tmp_redir;
	char	*tmp_file;

	tmp_redir = *redir;
	while (tmp_redir)
	{
		tmp_file = ft_strtrim(tmp_redir->file, " ");
		if (!tmp_file)
		{
			tmp_redir = tmp_redir->next;
			continue ;
		}
		free(tmp_redir->file);
		tmp_redir->file = tmp_file;
		tmp_redir = tmp_redir->next;
	}
}

static void	trim_args(char **args)
{
	int		i;
	char	*tmp;

	if (!args || !args[0])
		return ;
	if (ft_strncmp(args[0], "echo", 6) == 0)
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
			return ;
		i++;
	}
	return ;
}

t_cmd	*ft_new_commands(t_token **tokens, char **env)
{
	t_cmd	*new_cmd;
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->redir = find_redir(*tokens, env);
	trim_files(&new_cmd->redir);
	new_cmd->args = get_args(tokens, env);
	trim_args(new_cmd->args);
	new_cmd->cmd = new_cmd->args[0];
	new_cmd->add_space = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

//needs expand func to work
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
		value = expand(env, (*tokens)->value, (*tokens)->expand);
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

t_cmd	*get_commands(t_token *tokens, char **env)
{
	t_token	*tmp;
	t_cmd	*head;

	tmp = tokens;
	head = NULL;
	while (tmp)
	{
		add_cmd(&head, ft_new_commands(&tmp, env));
		if (ft_isspecial(tmp))
			while (tmp && tmp->type != TOKEN_PIPE)
				tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (head);
}
