#include "../inc/minishell.h"

int	cd_path(t_shell *shell, char *path)
{
	char	*oldpwd;
	char	*pwd;
	char	*aux;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		shell->exit_status = 1;
		return (1);
	}
	pwd = getcwd(NULL, 0);
	aux = ft_strjoin("OLDPWD=", oldpwd);
	shell->env = ft_add_modify_env(shell->env, aux);
	free(aux);
	free(oldpwd);
	aux = ft_strjoin("PWD=", pwd);
	shell->env = ft_add_modify_env(shell->env, aux);
	free(aux);
	free(pwd);
	shell->exit_status = 0;
	return (0);
}

int	cd_home(t_shell *shell)
{
	char	*home;

	home = ft_getenv(shell->env, "HOME");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		shell->exit_status = 1;
		return (1);
	}
	return (cd_path(shell, home));
}

int	cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = ft_getenv(shell->env, "OLDPWD");
	if (!oldpwd)
	{
		printf("minishell: cd: OLDPWD not set\n");
		shell->exit_status = 1;
		return (1);
	}
	printf("%s\n", oldpwd);
	return (cd_path(shell, oldpwd));
}

int	exec_cd(t_shell *shell, t_cmd *cmd)
{
    char	*path;

    path = cmd->args[1];
    if (!path || !ft_strcmp_order(path, "~"))
		return cd_home(shell);
	if (!ft_strcmp_order(path, "-"))
		return cd_oldpwd(shell);
	return cd_path(shell, path);
}
