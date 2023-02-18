/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:08:07 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/17 07:45:34 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

static int	execute_internal(t_shell *shell, t_cmd *cmd, int *status)
{
	if (check_builtin(shell, cmd, status))
		return (0);
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd->name, 2);
	*status = 1;
	return (1);
}

int	execute(t_shell *shell, char *line, int *status)
{
	t_cmd	cmd;
	int		result;

	if (!line || !*line)
		return (0);
	if (parse_command(line, &cmd, shell))
	{
		*status = 1;
		return (1);
	}
	result = execute_internal(shell, &cmd, status);
	ft_free_split(cmd.args);
	free(cmd.name);
	return (result);
}
