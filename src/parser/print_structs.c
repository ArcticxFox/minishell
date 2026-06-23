/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:37:27 by ejones            #+#    #+#             */
/*   Updated: 2026/06/23 16:53:41 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_WORD)
			ft_printf("[WORD]      :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_PIPE)
			ft_printf("[PIPE]      :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_REDIR_IN)
			ft_printf("[REDIR_IN]  :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_REDIR_OUT)
			ft_printf("[REDIR_OUT] :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_APPEND)
			ft_printf("[APPEND]    :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_HEREDOC)
			ft_printf("[HERE_DOC]  :\t%s, %d\n", tokens->value, tokens->expand);
		tokens = tokens->next;
	}
}

void	print_commands(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redir;
		i = 0;
		ft_printf("cmd : %s\n", cmd->cmd);
		ft_printf("args : ");
		while (cmd->args[i])
		{
			ft_printf("%s, ", cmd->args[i]);
			i++;
		}
		ft_printf("\n");
		while (redir)
		{
			ft_printf("file:%s\ndelimiter:%s\n", redir->file, redir->delimiter);
			redir = redir->next;
		}
		ft_printf("\n");
		cmd = cmd->next;
	}
}
