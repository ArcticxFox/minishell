/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:26:18 by ejones            #+#    #+#             */
/*   Updated: 2026/07/08 15:34:31 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int			g_value_exit;
extern volatile int	g_heredoc_interrupt;

void	heredoc_sigint(int sig);
void	init_signals(void);

#endif
