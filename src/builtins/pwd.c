/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:45:46 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 03:48:40 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "builtins.h"
#include "environment.h"
#include "libft.h"

int	pwd_builtin(t_shell *shell, const t_cmd *cmd)
{
	char	*pwd;

	if (cmd->args[0])
	{
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
		return (1);
	}
	pwd = get_env(shell->env, "PWD");
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (0);
}
