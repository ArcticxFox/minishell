/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:18:05 by ejones            #+#    #+#             */
/*   Updated: 2026/07/03 15:15:36 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	shell.should_exit = 0;
	tokens = NULL;
	head = NULL;
	init_signals();
	read_old_history(&shell);
	while (1)
	{
		line = readline("minishell> ");
		if (!line) // Ctrl+D
		{
			free_memory(shell.env);
			rl_clear_history();
			printf("exit\n");
			exit(g_value_exit);
		}
		if (line[0] != '\0')
			append_hist(shell.env, line);
			// add_history(line);
		tokens = lexer(line);
		if (!tokens)
		{
			free(line);
			continue;
		}
		head = get_commands(tokens, shell.env);
		shell.head = head;
		// print_commands(head);
		while (tokens)
			ft_delete_front_token(&tokens);
		setup_heredocs(head, shell.env);
		execute(head, &shell);
		printf("\n");
		while(head)
			ft_delete_front_cmd(&head);
		if (shell.should_exit)
		{
			free_memory(shell.env);
			rl_clear_history();
			exit(g_value_exit);
		}
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
