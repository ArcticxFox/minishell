/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:18:05 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 16:56:44 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_line(char *line, t_token **tokens, t_shell *shell)
{
	line = readline("minishell> ");
	if (g_signal_received)
	{
		shell->exit_value = 128 + g_signal_received;
		g_signal_received = 0;
	}
	if (!line)
	{
		free_memory(shell->env);
		rl_clear_history();
		printf("exit\n");
		exit(shell->exit_value);
	}
	if (line[0] != '\0')
		add_history(line);
	*tokens = lexer(line, shell);
	if (!*tokens)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	shell_execution(char *line, t_shell *shell, t_token *tokens)
{
	t_cmd	*cmd;

	shell->head = get_commands(shell, tokens);
	while (tokens)
		ft_delete_front_token(&tokens);
	cmd = shell->head;
	while (cmd
		&& setup_heredocs(shell->head, cmd->redir, shell->env, shell) == 0)
		cmd = cmd->next;
	if (cmd)
	{
		ft_delete_cmd(&shell->head);
		free(line);
		return (1);
	}
	execute(shell->head, shell);
	ft_delete_cmd(&shell->head);
	free(line);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_bzero(&shell, sizeof(t_shell));
	shell.env = copy_env(envp);
	tokens = NULL;
	line = NULL;
	init_signals();
	while (1)
	{
		if (check_line(line, &tokens, &shell))
			continue ;
		if (shell_execution(line, &shell, tokens))
			continue ;
		if (shell.should_exit == 1)
		{
			rl_clear_history();
			free_memory(shell.env);
			break ;
		}
		printf("exit = %d\n", shell.exit_value);
	}
	return (shell.exit_value);
}
