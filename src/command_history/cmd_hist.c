/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_hist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 15:04:39 by ejones            #+#    #+#             */
/*   Updated: 2026/06/24 18:51:40 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_old_history(t_shell *shell)
{
	int		fd;
	char	*tmp;
	char	*line;

	(void)shell;
	fd = open("cmd_hist.txt", O_RDONLY);
	if (fd == -1)
		return ;
	while ((line = get_next_line(fd)) != NULL)
	{
		tmp = ft_strtrim(line, "\n");
		add_history(tmp);
		free(line);
		free(tmp);
	}
	close(fd);
}

void	append_hist(char *line)
{
	int		fd;

	fd = open("cmd_hist.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		add_history(line);
		ft_putendl_fd(line, fd);
		close(fd);
	}
}

