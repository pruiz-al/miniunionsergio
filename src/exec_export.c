/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenitez <sbenitez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:08:00 by sbenitez          #+#    #+#             */
/*   Updated: 2025/05/27 12:21:24 by sbenitez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_env(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**ft_add_modify_env(char **env, char *str)
{
	char	*key;
	int		index;
	int		size;
	char	**new;
	int		i;

	key = ft_get_key(str);
	index = ft_search_env(env, key);
	free(key);
	if (index != -1)
	{
		free(env[index]);
		env[index] = ft_strdup(str);
		return (env);
	}
	size = ft_size_matrix(env);
	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < size)
		new[i] = ft_strdup(env[i]);
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	return (ft_free_matrix(env), new);
}

void	ft_sort_matrix(char **matrix)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (matrix[j])
	{
		i = 0;
		while (matrix[i + 1])
		{
			if (ft_strcmp(matrix[i], matrix[i + 1]) > 0)
				ft_swap(&matrix[i], &matrix[i + 1]);
			i++;
		}
		j++;
	}
}

void	ft_print_export(char **env)
{
	char	**new_env;
	int		i;
	char	*equal;

	if (!env)
		return ;
	new_env = ft_copy_env(env);
	if (!new_env)
		return ;
	ft_sort_matrix(new_env);
	i = 0;
	while (new_env[i])
	{
		equal = ft_strchr(new_env[i], '=');
		if (!equal)
			printf("declare -x %s\n", new_env[i]);
		else
		{
			*equal = '\0';
			printf("declare -x %s=\"%s\"\n", new_env[i], equal + 1);
			*equal = '=';
		}
		i++;
	}
	ft_free_matrix(new_env);
}

int	exec_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		ft_print_export(shell->env);
		return (0);
	}
	while (cmd->args[i])
	{
		if (!ft_check_env(cmd->args[i]))
		{
			printf("minishell: export: %s: not a \
valid identifier\n", cmd->args[i]);
			shell->exit_status = 1;
		}
		else
		{
			shell->env = ft_add_modify_env(shell->env, cmd->args[i]);
		}
		i++;
	}
	return (0);
}
