/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:41:16 by ejones            #+#    #+#             */
/*   Updated: 2026/04/23 18:57:54 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


void	print_token(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_WORD)
			printf("[WORD]      :\t%s : %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_PIPE)
			printf("[PIPE]      :\t%s : %d\n", tokens->value, tokens->expand);
 		else if (tokens->type == TOKEN_REDIR_IN)
			printf("[REDIR_IN]  :\t%s : %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_REDIR_OUT)
			printf("[REDIR_OUT] :\t%s : %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_APPEND)
			printf("[APPEND]    :\t%s : %d\n", tokens->value, tokens->expand);
		else if (tokens->type == TOKEN_HEREDOC)
			printf("[HERE_DOC]  :\t%s : %d\n", tokens->value, tokens->expand);
		tokens = tokens->next;
	}
}
t_token	*ft_last_token(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_add_token_back(t_token **lst, t_token *new)
{
	t_token	*end_node;

	if (lst != NULL && new != NULL)
	{
		if (*lst != NULL)
		{
			end_node = *lst;
			end_node = ft_last_token(end_node);
			end_node->next = new;
		}
		else
			*lst = new;
	}
}

t_token	*ft_new_token(char *value, t_token_type type, int expand)
{
	t_token	*new_token;


	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	new_token->expand = expand;
	new_token->type = type;
	if (type == TOKEN_WORD)
		new_token->value = value;
	else
		new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	return (new_token);
}

void	ft_delete_front_token(t_token **stack)
{
	t_token	*pstemp;

	pstemp = NULL;
	if (!stack && !*stack)
		return ;
	pstemp = *stack;
	if (pstemp->next == NULL)
		*stack = NULL;
	else
		*stack = pstemp->next;
	free(pstemp->value);
	free(pstemp);
}
