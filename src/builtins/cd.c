/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 01:28:15 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/15 17:58:30 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "builtins.h"
#include "libft.h"
#include "environment.h"

int	set_env_vars(t_shell *shell, const char *path)
{
	char	*old_pwd;
	char	*pwd;

	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	old_pwd = get_env(shell->secret_env, "PWD");
	pwd = getcwd(0, 0);
	set_env(shell, "OLDPWD", old_pwd);
	set_env(shell, "PWD", pwd);
	set_secret_env(shell, "OLDPWD", old_pwd);
	set_secret_env(shell, "PWD", pwd);
	free(old_pwd);
	free(pwd);
	return (0);
}

int	cd_builtin(t_shell *shell, const t_cmd *cmd)
{
	char	*path;

	if (cmd->argc > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!cmd->argc)
		path = get_env(shell->secret_env, "HOME");
	else
		path = cmd->args[0];
	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	return (set_env_vars(shell, path));
}
