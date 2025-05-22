#include "../inc/minishell.h"

int	ft_check_env(char *str)
{
	int	i;

	i = 0;
	if (!str || !ft_isalpha(str[0]) ||str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_search_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if(!ft_strncmp(env[i], name, ft_strlen(name)) && env[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return -1;
}

char	*ft_get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strdup(str);
	while (key[i] && key[i] != '=')
		i++;
	key[i] = '\0';
	return (key);
}

int	ft_size_env(char **env)
{
	int	i;

	i = 0;
	while(env && env[i])
		i++;
	return (i);
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
	size = ft_size_env(env);
	new = ft_malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = env[i];
		i++;
	}
	new[i] = ft_strdup(str);
	new[i+1] = NULL;
	free(env);
	return (new);
}

void	ft_print_export(char **env)
{
	char	**new_env;
	int		i;
	char	*equal;

	new_env = ft_copy_env(env);
	ft_sort_matrix(new_env);
	i = 0;
	while (new_env[y])
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
	ft_free_matrix(new);
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
			printf("minishell: export: %s: not a valid identifier\n", cmd->args[i]);
			ms->exit_status = 1;
		}
		else
		{
			shell->env = ft_add_modify_env(shell->env, cmd->args[i]);
		}
		i++;
	}
	return (0);
}
