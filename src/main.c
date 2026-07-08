/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:18:05 by ejones            #+#    #+#             */
/*   Updated: 2026/07/08 16:16:20 by ejones           ###   ########.fr       */
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
	t_cmd	*cmd;
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = copy_env(envp);
	shell.should_exit = 0;
	tokens = NULL;
	head = NULL;
	init_signals();
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
			add_history(line);
		tokens = lexer(line);
		if (!tokens)
		{
			free(line);
			continue;
		}
		head = get_commands(tokens, shell.env);
		shell.head = head;
		while (tokens)
			ft_delete_front_token(&tokens);
		cmd = head;
		while (cmd && setup_heredocs(head, cmd->redir, shell.env) == 0)
			cmd = cmd->next;
		if (cmd)
		{
			ft_delete_cmd(&head);
			free(line);
			continue ;
		}
		execute(head, &shell);
		ft_delete_cmd(&head);
		free(line);
		if (shell.should_exit == 1)
		{
			rl_clear_history();
			free_memory(shell.env);
			break;
		}
	}
	return (g_value_exit);
}
