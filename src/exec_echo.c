/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenitez <sbenitez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:22:07 by sbenitez          #+#    #+#             */
/*   Updated: 2025/05/19 17:22:28 by sbenitez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_flag(char *s)
{
	int	i;

	if (s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

int	exec_echo(t_shell *shell)
{
	int	i;
	int	nl_flag;

	if (!shell->cmd_lst->args[1])
	{
		printf("\n");
		return (0);
	}
	i = 1;
	nl_flag = 1;
	while (shell->cmd_lst->args[i] && ft_check_flag(shell->cmd_lst->args[i]))
	{
		nl_flag = 0;
		i++;
	}
	while (shell->cmd_lst->args[i])
	{
		printf("%s", shell->cmd_lst->args[i]);
		if (shell->cmd_lst->args[i + 1])
			printf(" ");
		i++;
	}
	if (nl_flag)
		printf("\n");
	return (0);
}
