/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:18:05 by ejones            #+#    #+#             */
/*   Updated: 2026/04/15 17:26:16 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

// la fonction readline() elle return NULL quand on fait Ctrl+D,
// line = null print exit car dans bash c'est ce qui ce passe
int	main(void)
{
	char *line;

	init_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Ctrl+D
		{
			printf("exit\n");
			exit(0);
		}
		if (line[0] != '\0')
			add_history(line);

		printf("You typed: %s\n", line);

		free(line);
	}
	return (0);
}
