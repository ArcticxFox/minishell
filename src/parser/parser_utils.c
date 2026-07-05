/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 20:20:33 by ejones            #+#    #+#             */
/*   Updated: 2026/07/05 17:03:36 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *tokens)
{
	int	n;

	n = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (ft_isspecial(tokens) == 2 && tokens->next)
			tokens = tokens->next->next;
		else
		{
			++n;
			tokens = tokens->next;
		}
	}
	return (n);
}

char	*get_cmd_value(t_token **tokens, char **env, bool *space)
{
	char	*value;

	value = NULL;
	while (*tokens && ft_isspecial(*tokens) == 2)
	{
		if (ft_isspecial(*tokens) == 2 && (*tokens)->next)
			*tokens = (*tokens)->next->next;
		else
			(*tokens) = (*tokens)->next;
	}
	if (!(*tokens) || ft_isspecial(*tokens) == 1)
		return (NULL);
	if ((*tokens)->value)
		value = expand(env, (*tokens)->value,
				(*tokens)->type, (*tokens)->expand);
	else
		value = NULL;
	*space = (*tokens)->space;
	(*tokens) = (*tokens)->next;
	return (value);
}

t_args	*get_args(t_token **tokens, char **env)
{
	int		n;
	t_args	*args;
	t_args	*new_args;

	n = count_args(*tokens) + 1;
	args = NULL;
	if (n < 1)
		return (NULL);
	while (n > 1)
	{
		new_args = malloc(sizeof(t_args));
		if (!new_args)
			return (NULL);
		new_args->next = NULL;
		new_args->value = get_cmd_value(tokens, env, &new_args->espace);
		if (!new_args->value)
		{
			ft_delete_front_args(&args);
			return (NULL);
		}
		add_args(&args, new_args);
		--n;
	}
	return (args);
}
