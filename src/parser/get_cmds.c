/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:38 by ejones            #+#    #+#             */
/*   Updated: 2026/06/29 20:52:55 by ejones           ###   ########.fr       */
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

t_cmd	*ft_new_commands(t_token **tokens, char **env)
{
	t_cmd	*new_cmd;
	// char	*tmp;
	// int		i;

	// i = 0;
	// tmp = NULL;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->redir = find_redir(*tokens, env);
	trim_files(&new_cmd->redir);
	new_cmd->args = get_args(tokens, env);
	if (!new_cmd->args)
	{
		while (new_cmd->redir)
			ft_delete_front_redir(&new_cmd->redir);
		free(new_cmd);
		return (NULL);
	}
	trim_args(new_cmd->args);
	new_cmd->cmd = new_cmd->args[0];
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*get_commands(t_token *tokens, char **env)
{
	t_token	*tmp;
	t_cmd	*new_node;
	t_cmd	*head;

	tmp = tokens;
	head = NULL;
	new_node = NULL;
	while (tmp)
	{
		new_node = ft_new_commands(&tmp, env);
		add_cmd(&head, new_node);
		if (ft_isspecial(tmp))
			while (tmp && tmp->type != TOKEN_PIPE)
				tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (head);
}
