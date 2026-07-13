/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 00:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/13 16:54:30 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	handle_file_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == TOKEN_REDIR_IN)
		fd = open(redir->file[0], O_RDONLY);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_APPEND)
		fd = open(redir->file[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	if (redir->type == TOKEN_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	read_heredoc_lines(t_shell *shell, int fd, t_cmd *head, t_redir *redir)
{
	char	*line;

	while (!g_heredoc_interrupt)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, redir->delimiter,
				ft_strlen(redir->delimiter) + 1))
		{
			free(line);
			break ;
		}
		if (redir->expand == true)
			line = expand_heredoc(shell, line);
		ft_putendl_fd(line, fd);
		free(line);
	}
	free_heredoc(head, shell->env, fd);
	if (g_heredoc_interrupt)
		exit(130);
	exit(0);
}

void	free_heredoc(t_cmd *head, char **env, int fd)
{
	close(fd);
	free_memory(env);
	rl_clear_history();
	ft_delete_cmd(&head);
}
