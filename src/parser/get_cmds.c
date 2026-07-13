/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:38 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 18:57:36 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*find_redir(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;
	t_redir	*redir;

	tmp = tokens;
	redir = NULL;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (ft_isspecial(tmp) == 2)
		{
			ft_add_back_redir(&redir, new_redir(shell, tmp));
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (redir);
}

t_cmd	*ft_new_commands(t_shell *shell, t_token **tokens)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->redir = find_redir(shell, *tokens);
	new_cmd->args = get_args(shell, tokens);
	if (!new_cmd->args || new_cmd->args[0][0] == '\0')
		new_cmd->cmd = NULL;
	else
		new_cmd->cmd = new_cmd->args[0];
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*get_commands(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;
	t_cmd	*new_node;
	t_cmd	*head;

	tmp = tokens;
	head = NULL;
	new_node = NULL;
	while (tmp)
	{
		new_node = ft_new_commands(shell, &tmp);
		add_cmd(&head, new_node);
		if (ft_isspecial(tmp))
			while (tmp && tmp->type != TOKEN_PIPE)
				tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (head);
}
