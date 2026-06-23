/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:41:16 by ejones            #+#    #+#             */
/*   Updated: 2026/06/23 13:09:26 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// fonction pour enlever les quotes aux extremiter
static char	*assign_value(char *value)
{
	char	*new_str;
	char	tmp;
	int		end;

	end = ft_strlen(value);
	if (value[end - 1] == ' ')
	{
		tmp = value[end - 2];
		value[end - 2] = value[end - 1];
		value[end - 1] = tmp;
	}
	if (*value == '\'')
		new_str = ft_strtrim(value, "\'");
	else if (*value == '"')
		new_str = ft_strtrim(value, "\"");
	else
		return (value);
	free(value);
	return (new_str);
}

t_token	*ft_new_token(char *value, t_tk_type type, int expand)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->next = NULL;
	new_token->expand = expand;
	if (*value == '\'')
		new_token->expand = 0;
	new_token->type = type;
	if (type == TOKEN_WORD)
		new_token->value = assign_value(value);
	else
		new_token->value = assign_value(value);
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
