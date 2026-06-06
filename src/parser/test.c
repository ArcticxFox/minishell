/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:38 by ejones            #+#    #+#             */
/*   Updated: 2026/06/06 17:15:25 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_isspecial(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_PIPE)
		return (1);
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		return (2);
	return (0);
}

t_cmd	tmp_get_commands(t_token *tokens)
{
	t_token	*tmp;
	t_cmd	*cmd;
	t_cmd	*head;

	tmp = tokens;
	cmd = NULL;
	head = NULL;
	while (tmp)
	{
		cmd = malloc(sizeof(t_cmd));
		if (ft_isspecial(tmp) == 2)
		{
			cmd->redir.type = tmp->type;
			tmp = tmp->next;
			cmd->redir.file = tmp->value;
		}
	}
}
