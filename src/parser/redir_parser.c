/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 13:33:56 by ejones            #+#    #+#             */
/*   Updated: 2026/06/29 20:28:22 by ejones           ###   ########.fr       */
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

t_redir	*ft_last_redir(t_redir *lst)
{
	t_redir	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_redir	*new_redir(t_token *tokens, char **env)
{
	t_redir	*new_redir;

	if (!tokens || !tokens->next)
		return (NULL);
	new_redir = malloc(sizeof(t_redir) * 1);
	if (!new_redir)
		return (NULL);
	if (tokens->next->value)
		new_redir->file = expand(env, tokens->next->value,
				tokens->next->expand);
	else
		new_redir->file = NULL;
	new_redir->type = tokens->type;
	if (tokens->type == TOKEN_HEREDOC)
		new_redir->delimiter = ft_strdup(new_redir->file);
	else
		new_redir->delimiter = NULL;
	new_redir->heredoc_fd = -1;
	new_redir->next = NULL;
	return (new_redir);
}

void	ft_add_back_redir(t_redir **lst, t_redir *new_cmd)
{
	t_redir	*end_node;

	if (lst != NULL && new_cmd != NULL)
	{
		if (*lst != NULL)
		{
			end_node = *lst;
			end_node = ft_last_redir(end_node);
			end_node->next = new_cmd;
		}
		else
			*lst = new_cmd;
	}
}

void	ft_delete_front_redir(t_redir **stack)
{
	t_redir	*pstemp;

	pstemp = NULL;
	if (!stack && !*stack)
		return ;
	pstemp = *stack;
	if (pstemp->next == NULL)
		*stack = NULL;
	else
		*stack = pstemp->next;
	if (pstemp->heredoc_fd >= 0)
		close(pstemp->heredoc_fd);
	free(pstemp->file);
	free(pstemp->delimiter);
	free(pstemp);
}
