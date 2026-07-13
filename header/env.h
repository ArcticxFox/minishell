/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:15:29 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 20:53:39 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// char	**copy_env(char **envp);
void	copy_env(char **envp, t_shell *shell);
char	*get_env_value(char **env, char *name);
void	set_env_value(char **env, char *name, char *new_val);
int		len_name(char *args);

int		ft_get_lenght(t_shell *shell, char *str);

#endif
