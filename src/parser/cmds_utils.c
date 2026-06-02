/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:49:28 by ejones            #+#    #+#             */
/*   Updated: 2026/06/02 15:50:10 by ejones           ###   ########.fr       */
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

void	ft_delete_front_cmd(t_cmd **stack)
{
	t_cmd	*pstemp;

	pstemp = NULL;
	if (!stack && !*stack)
		return ;
	pstemp = *stack;
	if (pstemp->next == NULL)
		*stack = NULL;
	else
		*stack = pstemp->next;
	if (pstemp->args)
		free_memory(pstemp->args);
	free(pstemp->cmd);
	free(pstemp);
}
