/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:14:06 by ejones            #+#    #+#             */
/*   Updated: 2026/07/14 17:01:26 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_interrupt_signal = 0;

// close(STDIN_FILENO)
// another way to interrupt readline
void	heredoc_sigint(int sig)
{
	(void)sig;
	g_interrupt_signal = 1;
	close(STDIN_FILENO);
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (rl_line_buffer && *rl_line_buffer)
		add_history(rl_line_buffer);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_interrupt_signal = SIGINT;
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
