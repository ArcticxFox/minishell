/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/11 13:26:39 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Helpers de construction (pas static pour éviter unused-function warnings) */

t_cmd	*new_cmd(char *cmd, char **args)
{
	t_cmd	*node;
	int		i;
	int		count;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = ft_strdup(cmd);
	count = 0;
	while (args[count])
		count++;
	node->args = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		node->args[i] = ft_strdup(args[i]);
		i++;
	}
	node->args[count] = NULL;
	node->redirs = NULL;
	node->next = NULL;
	return (node);
}

void	add_redir(t_cmd *cmd, char *file, t_tk_type type)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->file = ft_strdup(file);
	new->type = type;
	new->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = new;
		return ;
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	link_pipe(t_cmd *a, t_cmd *b)
{
	while (a->next)
		a = a->next;
	a->next = b;
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->cmd);
		i = 0;
		while (cmd->args && cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		free_redirs(cmd->redirs);
		free(cmd);
		cmd = tmp;
	}
}

char	**copy_env_test(char **envp)
{
	char	**copy;
	int		i;
	int		count;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

/* === TESTS === */

t_cmd	*test_ls_pipe_cat(void)
{
	t_cmd	*c1;
	t_cmd	*c2;

	c1 = new_cmd("ls", (char *[]){"ls", NULL});
	c2 = new_cmd("cat", (char *[]){"cat", NULL});
	link_pipe(c1, c2);
	return (c1);
}

t_cmd	*test_three_pipes(void)
{
	t_cmd	*c1;
	t_cmd	*c2;
	t_cmd	*c3;

	c1 = new_cmd("ls", (char *[]){"ls", "-la", NULL});
	c2 = new_cmd("grep", (char *[]){"grep", ".c", NULL});
	c3 = new_cmd("wc", (char *[]){"wc", "-l", NULL});
	link_pipe(c1, c2);
	link_pipe(c1, c3);
	return (c1);
}

t_cmd	*test_pipe_with_redir_out(void)
{
	t_cmd	*c1;
	t_cmd	*c2;

	c1 = new_cmd("ls", (char *[]){"ls", NULL});
	c2 = new_cmd("grep", (char *[]){"grep", ".c", NULL});
	add_redir(c2, "output.txt", TOKEN_REDIR_OUT);
	link_pipe(c1, c2);
	return (c1);
}

t_cmd	*test_pipe_with_redir_in(void)
{
	t_cmd	*c1;
	t_cmd	*c2;

	c1 = new_cmd("cat", (char *[]){"cat", NULL});
	add_redir(c1, "Makefile", TOKEN_REDIR_IN);
	c2 = new_cmd("wc", (char *[]){"wc", "-l", NULL});
	link_pipe(c1, c2);
	return (c1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_cmd	*cmds;

	(void)ac;
	(void)av;
	shell.env = copy_env_test(envp);

	/* === CHOISIS TON TEST ICI === */
	// cmds = test_ls_pipe_cat();
	// cmds = test_three_pipes();
	// cmds = test_pipe_with_redir_out();
	cmds = test_pipe_with_redir_in();

	shell.head = cmds;

	printf("=== Lancement du test ===\n");
	execute_pipeline(cmds, &shell);
	printf("=== Fin du test ===\n");

	free_cmds(cmds);
	free_env(shell.env);
	return (0);
}
