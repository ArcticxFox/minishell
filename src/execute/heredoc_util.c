/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 15:58:49 by ejones            #+#    #+#             */
/*   Updated: 2026/06/30 18:12:45 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(char **env, char *line)
{
	char	*tmp;

	tmp = expand(env, line, TOKEN_WORD, 1);
	if (!tmp)
		return (NULL);
	free(line);
	return (tmp);
}
