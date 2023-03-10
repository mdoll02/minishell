/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:06:08 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/09 17:52:57 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// I need:
// argc, argv, envp
// TODO need to test code

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "types.h"
#include "execution.h"

void	call_child_process(t_cmd *cmd, int counter, t_shell *shell, int *status)
{
	int		pid;
	int		end[2];

	*status = pipe(end);
	if (*status == -1)
		return ;
	pid = fork();
	if (pid == -1)
	{
		*status = pid;
		return ;
	}
	if (pid == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		execute(shell, cmd->args[counter], status);
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		waitpid(pid, NULL, WNOHANG);
	}
}

int	pipes(t_shell *shell, t_cmd *cmd)
{
	int	counter;
	int	status;

	counter = 0;
	dup2(CT_RED_IN, STDIN_FILENO);
	while (counter < cmd->nb_pipes)
	{
		call_child_process(cmd, counter, shell, &status);
		if (status == -1)
			return (status);
		counter++;
	}
	dup2(CT_RED_OUT, STDOUT_FILENO);
	execute(shell, cmd->args[counter], &status);
	return (status);
}
