/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:02:29 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 00:10:09 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "builtins.h"
#include "libft.h"

// TODO: support cd - and cd ~ using get_env and set_env
int	cd_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	//char	*oldpwd;
	//char	*pwd;

	(void)shell;
	if (cmd->argc > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	//if (cmd->argc == 1)
	//	path = get_env(shell->env, "HOME");
	//else
	path = cmd->args[1];
	if (!path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	//oldpwd = get_env(shell->env, "PWD");
	//pwd = getcwd(NULL, 0);
	//set_env(shell->env, "OLDPWD", oldpwd);
	//set_env(shell->env, "PWD", pwd);
	//free(oldpwd);
	//free(pwd);
	return (0);
}