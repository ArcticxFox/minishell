/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:18:05 by ejones            #+#    #+#             */
/*   Updated: 2026/04/23 18:30:36 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	lenx;

	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	lenx = (len1 + ft_strlen(s2));
	s3 = (char *)ft_calloc((lenx + 1), sizeof(char));
	if (!s3)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(s3, s1, (len1 + 1));
		free(s1);
	}
	ft_strlcpy(&s3[len1], s2, ft_strlen(s2) + 1);
	return (s3);
}

// la fonction readline() elle return NULL quand on fait Ctrl+D,
// line = null print exit car dans bash c'est ce qui ce passe
int	main(int ac, char **av)
{
	//char *line;
	(void)ac;
	lexer(av[1]);
	// init_signals();
	// while (1)
	// {
	// 	line = readline("minishell> ");
	// 	if (!line) // Ctrl+D
	// 	{
	// 		printf("exit\n");
	// 		exit(0);
	// 	}
	// 	if (line[0] != '\0')
	// 		add_history(line);

	// 	printf("You typed: %s\n", line);
	// 	lexer(line);
	// 	printf("\n");
	// 	free(line);
	// }
	return (g_value_exit);
}
