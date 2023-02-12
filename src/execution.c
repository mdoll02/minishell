/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:08:07 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/12 23:43:39 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"
#include "libft.h"
#include "parsing.h"

int	check_builtin(t_shell *shell, t_cmd *cmd, int *status)
{
	int	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strncmp(g_builtins[i].name, cmd->name, 1000) == 0)
		{
			*status = g_builtins[i].func(shell, cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

int	execute(t_shell *shell, char *line)
{
	int		status;
	t_cmd	cmd;

	parse_command(line, &cmd);
	if (check_builtin(shell, &cmd, &status))
		return (status);
	return (1);
}
