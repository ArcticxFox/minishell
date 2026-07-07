/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 15:04:39 by ejones            #+#    #+#             */
/*   Updated: 2026/07/07 19:58:59 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_log_env(t_shell *shell)
{
	char	*path;
	char	*log_path[3];

	log_path[0] = "export";
	log_path[1] = get_env_value(shell->env, "PWD");
	log_path[2] = NULL;
	path = ft_strjoin("CMD_LOG=", log_path[1]);
	path = ft_strjoin_free(path, "/cmd_log.txt");
	log_path[1] = path;
	exec_export(log_path, shell);
	free(path);
}

void	read_old_history(t_shell *shell)
{
	int		fd;
	char	*tmp;
	char	*line;
	char	*path;

	if (!get_env_value(shell->env, "CMD_LOG"))
		add_cmd_log_env(shell);
	path = get_env_value(shell->env, "CMD_LOG");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = ft_strtrim(line, "\n");
		add_history(tmp);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
}

void	append_hist(char **env, char *line)
{
	int		fd;
	char	*log_path;

	log_path = get_env_value(env, "CMD_LOG");
	fd = open(log_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		add_history(line);
		ft_putendl_fd(line, fd);
		close(fd);
	}
}
