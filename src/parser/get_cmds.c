/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:14:19 by ejones            #+#    #+#             */
/*   Updated: 2026/06/02 16:13:12 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_isspecial(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_PIPE || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

char	count_cmdargs(t_token *tokens)
{
	int	size;

	size = 0;
	if (tokens != NULL && !ft_isspecial(tokens))
	{
		size = 1;
		size += count_cmdargs(tokens->next);
	}
	return (size);
}

char	**get_args(t_token **tokens, t_filetype filetype)
{
	int		i;
	int		nbr_tk;
	char	**args;

	i = 0;
	if (filetype == NOT_FILE)
		nbr_tk = count_cmdargs(*tokens);
	else
		nbr_tk = 2;
	args = (char **)ft_calloc(nbr_tk + 1, sizeof(char *));
	if (!args)
		return (NULL);
	while (i < nbr_tk)
	{
		args[i] = ft_strdup((*tokens)->value);
		if (!args[i])
		{
			free_memory(args);
			return (NULL);
		}
		++i;
		*tokens = (*tokens)->next;
	}
	return (args);
}

t_cmd	*ft_new_cmd(char *cmd, t_token **tokens, t_filetype filetype, t_tk_type tk_type)
{
	t_cmd	*new_cmd;

	new_cmd = NULL;
	if (!cmd || !tokens)
		return (NULL);
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = ft_strdup(cmd);
	if (!*tokens)
		new_cmd->expand = 0;
	else
		new_cmd->expand = (*tokens)->expand;
	if (!*tokens)
		new_cmd->args = NULL;
	else if ((*tokens)->type == TOKEN_REDIR_IN || (*tokens)->type == TOKEN_REDIR_OUT
		|| (*tokens)->type == TOKEN_APPEND || (*tokens)->type == TOKEN_HEREDOC)
		new_cmd->args = get_args(tokens, filetype);
	else
		new_cmd->args = get_args(tokens, filetype);
	new_cmd->filetype = filetype;
	new_cmd->tk_type = tk_type;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*get_special_cmd(t_token **token)
{
	t_cmd	*cmd;
	t_token	*tmp;

	cmd = NULL;
	tmp = NULL;
	if ((*token)->type == TOKEN_REDIR_IN || (*token)->type == TOKEN_REDIR_OUT
		|| (*token)->type == TOKEN_APPEND || (*token)->type == TOKEN_HEREDOC)
	{
		tmp = *token;
		*token = (*token)->next;
	}
	cmd = ft_new_cmd((*token)->value, &tmp, IS_FILE, (*token)->type);
	if (!cmd)
		return (NULL);
	return (cmd);
}

t_cmd	*get_commands(t_token *tokens)
{
	t_token	*tmp;
	t_cmd	*cmd;
	t_cmd	*head;

	tmp = tokens;
	cmd = NULL;
	head = NULL;
	while(tmp)
	{
		if (ft_isspecial(tmp))
		{
			cmd = get_special_cmd(&tmp);
			tmp = tmp->next;
		}
		else
			cmd = ft_new_cmd(tmp->value, &tmp, NOT_FILE, tmp->type);
		if (!cmd)
				break;
		add_cmd(&head, cmd);
	}
	if (!tmp)
		return (head);
	return (NULL);
}
