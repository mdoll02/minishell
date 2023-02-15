/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 04:07:07 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/13 04:28:55 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "libft.h"
#include "environment.h"

int	unset_builtin(t_shell *shell, const t_cmd *cmd)
{
	int	i;

	if (cmd->argc == 0)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return (1);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
			return (1);
		}
		remove_env(shell, cmd->args[i]);
		i++;
	}
	return (0);
}
