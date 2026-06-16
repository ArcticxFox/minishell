/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:43:20 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/11 12:00:00 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/* Contexte de pipeline, local à ce fichier (ne pollue pas structs.h) */
typedef struct s_pipectx
{
	int	**pipes;
	int	n_cmds;
	int	idx;
}	t_pipectx;

/* Prototypes internes */
static void	close_all_pipes(int **pipes, int n);
static void	child_pipe_setup(t_cmd *cmd, t_pipectx *ctx, t_shell *shell);

static int	apply_redirs(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == TOKEN_REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (-1);
		if (redir->type == TOKEN_REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

void	execute_child(t_cmd *cmd, int fd_in, int fd_out, t_shell *shell)
{
	char	*path;

	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (apply_redirs(cmd->redirs) < 0)
		exit(1);
	if (is_builtin(cmd->cmd))
	{
		builtin(cmd->args, shell);
		exit(0);
	}
	path = get_path(cmd->cmd, shell);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror(path);
	free(path);
	exit(127);
}

int	count_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	free_pipes(int **pipes, int i)
{
	while (i > 0)
	{
		i--;
		free(pipes[i]);
	}
	free(pipes);
}

int	**create_pipes(int n)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		return (NULL);
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			free_pipes(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) < 0)
		{
			free(pipes[i]);
			free_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	close_all_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	child_pipe_setup(t_cmd *cmd, t_pipectx *ctx, t_shell *shell)
{
	int	fd_in;
	int	fd_out;

	if (ctx->idx == 0)
		fd_in = STDIN_FILENO;
	else
		fd_in = ctx->pipes[ctx->idx - 1][0];
	if (ctx->idx == ctx->n_cmds - 1)
		fd_out = STDOUT_FILENO;
	else
		fd_out = ctx->pipes[ctx->idx][1];
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);
	close_all_pipes(ctx->pipes, ctx->n_cmds - 1);
	execute_child(cmd, STDIN_FILENO, STDOUT_FILENO, shell);
}

void	execute_pipeline(t_cmd *list, t_shell *shell)
{
	t_pipectx	ctx;
	pid_t		*pids;
	t_cmd		*cur;
	int			i;

	ctx.n_cmds = count_cmds(list);
	ctx.pipes = create_pipes(ctx.n_cmds - 1);
	pids = malloc(sizeof(pid_t) * ctx.n_cmds);
	if (!ctx.pipes || !pids)
		return ;
	cur = list;
	i = 0;
	while (cur)
	{
		ctx.idx = i;
		pids[i] = fork();
		if (pids[i] == 0)
			child_pipe_setup(cur, &ctx, shell);
		cur = cur->next;
		i++;
	}
	close_all_pipes(ctx.pipes, ctx.n_cmds - 1);
	i = 0;
	while (i < ctx.n_cmds)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free_pipes(ctx.pipes, ctx.n_cmds - 1);
	free(pids);
}

int	is_builtin(char *cmd)
{
	static t_builtin	builtin[8] = {
	{"pwd", NULL},
	{"echo", NULL},
	{"exit", NULL},
	{"env", NULL},
	{"cd", NULL},
	{"export", NULL},
	{"unset", NULL},
	{NULL, NULL}
	};
	int					i;

	i = 0;
	while (builtin[i].name)
	{
		if (!ft_strncmp(cmd, builtin[i].name, ft_strlen(builtin[i].name) + 1))
			return (1);
		i++;
	}
	return (0);
}
