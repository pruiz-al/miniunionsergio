/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenitez <sbenitez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:04:06 by sbenitez          #+#    #+#             */
/*   Updated: 2025/05/27 12:05:37 by sbenitez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cd_path(t_shell *shell, char *path)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (ft_check_errors(shell, oldpwd, path))
	{
		shell->exit_status = 1;
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_add_modify_env(shell->env, "PWD=");
		free (oldpwd);
		shell->exit_status = 1;
		return (1);
	}
	if (!ft_update_pwd(shell, oldpwd, pwd))
		shell->exit_status = 0;
	else
		shell->exit_status = 1;
	free(oldpwd);
	free(pwd);
	return (0);
}

int	cd_home(t_shell *shell)
{
	char	*home;
	char	*pwd;
	char	*oldpwd;

	home = ft_getenv(shell->env, "HOME");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		shell->exit_status = 1;
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(home) < 0)
		return(ft_check_home_error(shell, home, oldpwd));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(home);
	ft_update_home(shell, oldpwd, pwd);
	free(home);
	free(oldpwd);
	free(pwd);
	shell->exit_status = 0;
	return (0);
}

int	cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;
	int		result;

	oldpwd = ft_getenv(shell->env, "OLDPWD");
	if (!oldpwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		shell->exit_status = 1;
		return (1);
	}
	printf("%s\n", oldpwd);
	result = cd_path(shell, oldpwd);
	free(oldpwd);
	return (result);
}

int	exec_cd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = cmd->args[1];
	if (!path || !ft_strcmp_order(path, "~"))
		return (cd_home(shell));
	if (!ft_strcmp_order(path, "-"))
		return (cd_oldpwd(shell));
	return (cd_path(shell, path));
}
