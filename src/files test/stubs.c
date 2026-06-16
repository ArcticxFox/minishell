/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stubs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/11 12:00:00 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Stubs pour les fonctions externes dont execute.c et execute_utils.c
** ont besoin, mais qu'on ne veut pas linker depuis le reste du projet
** (pour isoler complètement le test de la partie execute).
*/

#include "../header/minishell.h"

/*
** get_env_value : récupère la valeur d'une variable d'env.
** Sémantique : on cherche une ligne qui commence par "name" (avec le '=' inclus
** si l'appelant le fournit, comme c'est le cas dans get_path avec "PATH=").
*/
char	*get_env_value(char **env, char *name)
{
	int		i;
	size_t	len;

	if (!env || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len))
			return (&env[i][len]);
		i++;
	}
	return (NULL);
}

/*
** Stub builtin : ne sera pas appelé dans nos tests (on utilise ls/cat/grep
** qui ne sont pas des builtins). Si tu testes echo/pwd/env, ça affichera
** juste les args.
*/
int	builtin(char **args, t_shell *shell)
{
	int	i;

	(void)shell;
	if (!args || !args[0])
		return (0);
	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	return (0);
}

/*
** Stub execute_single : référencé par execute() dans execute.c.
** On ne l'appelle pas dans nos tests de pipeline.
*/
void	execute_single(t_cmd *list, t_shell *shell)
{
	(void)list;
	(void)shell;
	ft_putstr_fd("[stub] execute_single appelee\n", 2);
}
