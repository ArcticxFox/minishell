/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_linked_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:49:28 by ejones            #+#    #+#             */
/*   Updated: 2026/07/08 16:41:10 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_args	*ft_last_arg(t_args *lst)
{
	t_args	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

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

void	add_args(t_args **lst, t_args *new_cmd)
{
	t_args	*end_node;

	if (lst != NULL && new_cmd != NULL)
	{
		if (*lst != NULL)
		{
			end_node = *lst;
			end_node = ft_last_arg(end_node);
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

void	ft_delete_cmd(t_cmd **stack)
{
	t_cmd	*pstemp;

	pstemp = NULL;
	if (!stack)
		return ;
	while (*stack)
	{
		pstemp = *stack;
		*stack = pstemp->next;
		while (pstemp->redir)
			ft_delete_front_redir(&pstemp->redir);
		while (pstemp->args)
			ft_delete_front_args(&pstemp->args);
		free(pstemp);
	}
}
