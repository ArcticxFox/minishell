/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_linked_lists.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 16:02:10 by ejones            #+#    #+#             */
/*   Updated: 2026/07/05 16:35:38 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_front_args(t_args **stack)
{
	t_args	*pstemp;

	pstemp = NULL;
	if (!stack || !*stack)
		return ;
	pstemp = *stack;
	if (pstemp->next == NULL)
		*stack = NULL;
	else
		*stack = pstemp->next;
	free(pstemp->value);
	free(pstemp);
}
