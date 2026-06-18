/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:18:05 by ejones            #+#    #+#             */
/*   Updated: 2026/06/18 14:23:52 by ejones           ###   ########.fr       */
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
int	main(int ac, char **av, char **envp)
{
	char *line;
	t_token	*tokens;
	t_cmd	*head;
	t_shell	shell;

	(void)ac;
	(void)av;

	shell.env = copy_env(envp);
	tokens = NULL;
	head = NULL;
	init_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Ctrl+D
		{
			free_memory(shell.env);
			printf("exit\n");
			exit(0);
		}
		if (line[0] != '\0')
			add_history(line);
		tokens = lexer(line);
		print_token(tokens);
		head = tmp_get_commands(tokens, shell.env);
		shell.head = head;
		print_commands(head);
		while (tokens)
		{
			ft_delete_front_token(&tokens);
		}
		while(head)
		{
			ft_delete_front_cmd(&head);
		}
		// printf("\n");
		free(line);
	}
	return (g_value_exit);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**cmd_args;
// 	char	*str;
// 	t_shell	shell;

// 	shell.env = copy_env(envp);
// 	(void)ac;
// 	(void)av;
// 	init_signals();
// 	while (1)
// 	{
// 		str = readline("minishell> ");
// 		cmd_args = ft_split(str, ' ');
// 		if (!str || !ft_strncmp(str, "exit", 5))
// 		{
// 			rl_clear_history();
// 			rl_free_line_state();
// 			free_all(&shell, cmd_args, str, 2);
// 			return (0);
// 		}
// 		if (cmd_args)
// 			builtin(cmd_args, &shell);
// 		free_all(&shell, cmd_args, str, 1);
// 	}
// 	return (0);
// }
