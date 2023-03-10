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
// TODO get them pipes working

#include <stdio.h>
#include "types.h"

// line 37 / 38 for syntax error?
static int	nb_of_pipes(char **args)
{
	int		nb_of_pipes;
	int		index_args;
	int		index_chars;

	nb_of_pipes = 0;
	index_args = 0;
	while (args[index_args])
	{
		index_chars = 0;
		while (args[index_args][index_chars])
		{
			if (args[index_args][index_chars] == '|')
				nb_of_pipes++;
			index_chars++;
			if (nb_of_pipes != 1)
				return (-1);
		}
		index_args++;
	}
	return (nb_of_pipes);
}

int	pipes(t_shell *shell, t_cmd *cmd)
{
	t_pipex	pipex;
	int		cmd_count;

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

void	open_files(t_pipex *pipex, char **argv, int argc)
{
	pipex->fd_outfile = open(argv[argc - 1], O_WRONLY | \
		O_TRUNC | O_CREAT, 0644);
	if (pipex->fd_outfile == -1)
		error_msg(argv[argc - 1], -1);
	pipex->fd_infile = open(argv[1], O_RDONLY);
	if (pipex->fd_infile == -1)
		error_msg(pipex->argv[1], pipex->fd_outfile);
}


void	error(char *str)
{
	perror(str);
	exit(1);
}

void	error_msg(char *str, int fd)
{
	if (fd != -1)
		write(fd, "       0\n", 9);
	write(STDERR_FILENO, "pipex: ", 7);
	perror(str);
	exit(0);
}
