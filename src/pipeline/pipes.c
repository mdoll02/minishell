/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:09:26 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/15 12:09:26 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>
#include "execution.h"
#include <stdlib.h>
#include <stdio.h>
#include "pipeline.h"
#include <sys/wait.h>

int	handle_pipe_case(t_shell *shell, t_cmd *cmd, int *status, t_fd_pipeline *pl)
{
	pid_t	pid;

	if (pipe(pl->pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pl->pipe_fd[0]);
		dup2(pl->input_fd, STDIN_FILENO);
		dup2(pl->pipe_fd[1], STDOUT_FILENO);
		if (pl->input_fd != STDIN_FILENO)
			close(pl->input_fd);
		close(pl->pipe_fd[1]);
		*status = execute_internal(shell, cmd, status);
		close(pl->pipe_fd[1]);
		exit(*status);
	}
	else
	{
		close(pl->pipe_fd[1]);
		pl->input_fd = pl->pipe_fd[0];
	}
	return (pl->input_fd);
}
