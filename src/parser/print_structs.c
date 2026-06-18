/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:37:27 by ejones            #+#    #+#             */
/*   Updated: 2026/06/18 14:24:23 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_WORD)
			printf("[WORD]      :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_PIPE)
			printf("[PIPE]      :\t%s, %d\n", tokens->value, tokens->expand);
 		else if (tokens->type == TOKEN_REDIR_IN)
			printf("[REDIR_IN]  :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_REDIR_OUT)
			printf("[REDIR_OUT] :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_APPEND)
			printf("[APPEND]    :\t%s, %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_HEREDOC)
			printf("[HERE_DOC]  :\t%s, %d\n", tokens->value, tokens->expand);
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
		printf("cmd : %s\n", cmd->cmd);
		printf("args : ");
		while(cmd->args[i])
		{
			printf("%s, ", cmd->args[i]);
			i++;
		}
		printf("\n");
		while(redir)
		{
			printf("file : %s\n", redir->file);
			redir = redir->next;
		}
		ft_printf("\n");
		cmd = cmd->next;
	}
}
