/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:15:29 by ejones            #+#    #+#             */
/*   Updated: 2026/05/19 17:43:37 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

char	**copy_env(char **envp);
char	*get_env_value(char **env, char *name);
void	set_env_value(char **env, char *name, char *new_val);
int		len_name(char *args);


//expander
int	ft_get_lenght(char **env, char *str);

#endif
