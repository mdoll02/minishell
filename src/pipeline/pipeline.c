/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:35:14 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/15 11:38:50 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>
#include "execution.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


static void	restore_std_fds(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

static int	handle_pipe_case(t_shell *shell, t_cmd *cmd, int *status,
								t_fd_pipeline *pl)
{
	if (pipe(pl->pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	if (fork() == 0)
	{
		close(pl->pipe_fd[0]);
		dup2(pl->input_fd, STDIN_FILENO);
		dup2(pl->pipe_fd[1], STDOUT_FILENO);
		close(pl->input_fd);
		close(pl->pipe_fd[1]);
		*status = execute_internal(shell, cmd, status);
		exit(*status);
	}
	else
	{
		close(pl->pipe_fd[1]);
		pl->input_fd = pl->pipe_fd[0];
	}
	return (pl->input_fd);
}

static int	handle_final_case(t_shell *shell, t_cmd *cmd,
								int *status, int input_fd)
{
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	*status = execute_internal(shell, cmd, status);
	return (*status);
}

static int	exec_pipeline_command(t_shell *shell, t_cmd **cmd, int *status,
					t_fd_pipeline *pl)
{
	if ((*cmd)->next_type == CT_PIPE)
	{
		pl->input_fd = handle_pipe_case(shell, *cmd, status, pl);
		if (pl->input_fd == 1)
			return (1);
	}
	else
	{
		*status = handle_final_case(shell, *cmd, status, pl->input_fd);
		return (0);
	}
	(*cmd)++;
	return (-1);
}

static int	redirect_input(t_cmd **cmd)
{
	int	open_ret;

	(*cmd)++;
	open_ret = open((*cmd)->name, O_RDONLY);
	if (open_ret == -1)
	{
		perror((*cmd)->name);
		return (open_ret);
	}
	(*cmd)++;
	return (open_ret);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd, int len, int *status)
{
	int				orig_stdin;
	int				orig_stdout;
	t_fd_pipeline	pl;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (cmd->next_type == CT_REDIRECT_IN)
	{
		pl.input_fd = redirect_input(&cmd);
		if (pl.input_fd == -1)
		{
			*status = 1;
			return (*status);
		}
		len -= 2;
	}
	else
		pl.input_fd = orig_stdin;
	while (len--)
	{
		if (exec_pipeline_command(shell, &cmd, status,
				&pl) != -1)
			break ;
	}
	restore_std_fds(orig_stdin, orig_stdout);
	return (*status);
}
