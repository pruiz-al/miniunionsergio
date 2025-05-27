/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenitez <sbenitez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:25:19 by sbenitez          #+#    #+#             */
/*   Updated: 2025/05/27 12:25:56 by sbenitez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_remove_env(char **env, char *str)
{
	char	*key;
	int		size;
	char	**new;
	int		i;
	int		j;

	size = ft_size_matrix(env);
	new = malloc(sizeof(char *) * size);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		key = ft_get_key(env[i]);
		if (ft_strcmp(key, str) != 0)
			new[j++] = ft_strdup(env[i]);
		free(key);
		i++;
	}
	new[j] = NULL;
	ft_free_matrix(env);
	return (new);
}

int	exec_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!ft_check_env(cmd->args[i]))
		{
			printf("minishell: unset: %s: \
not a valid identifier\n", cmd->args[i]);
			shell->exit_status = 1;
		}
		else
			shell->env = ft_remove_env(shell->env, cmd->args[i]);
		i++;
	}
	return (0);
}
