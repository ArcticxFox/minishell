#include "../header/minishell.h"

t_token	*ft_token_new(char *str, t_token_type token_type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->type = token_type;
	new_node->str = ft_strdup(str);
	return (new_node);
}

t_token	*ft_token_last(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*end_node;

	if (lst != NULL && new != NULL)
	{
		if (*lst != NULL)
		{
			end_node = *lst;
			end_node = ft_token_last(end_node);
			end_node->next = new;
		}
		else
			*lst = new;
	}
}

void	ft_token_delete_front(t_token **stack)
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
	free(pstemp->str);
	free(pstemp);
}
