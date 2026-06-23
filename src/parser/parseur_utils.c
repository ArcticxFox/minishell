/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:49:28 by ejones            #+#    #+#             */
/*   Updated: 2026/06/23 13:41:15 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_cmd	*ft_last_cmd(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
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

void	add_cmd(t_cmd **lst, t_cmd *new_cmd)
{
	t_cmd	*end_node;

	if (lst != NULL && new_cmd != NULL)
	{
		if (*lst != NULL)
		{
			end_node = *lst;
			end_node = ft_last_cmd(end_node);
			end_node->next = new_cmd;
		}
		else
			*lst = new_cmd;
	}
}
