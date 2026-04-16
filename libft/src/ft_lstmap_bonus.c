/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:11:44 by ejones            #+#    #+#             */
/*   Updated: 2026/01/02 13:57:47 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_node = NULL;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			del(f(lst->content));
			ft_lstclear(&new_node, del);
			return (NULL);
		}
		ft_lstadd_back(&new_node, tmp);
		lst = lst->next;
	}
	tmp->next = NULL;
	return (new_node);
}
