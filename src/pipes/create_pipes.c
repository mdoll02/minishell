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

int	pipes(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		cmd_count;

	if (argc < 5)
		error("Invalid number of arguments");
	cmd_count = 2;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.argc = argc;
	open_files(&pipex, argv, argc);
	pipex.env_paths = get_env_paths(envp);
	dup2(pipex.fd_infile, STDIN_FILENO);
	while (cmd_count < argc - 2)
	{
		ft_pipex(pipex, cmd_count);
		cmd_count++;
	}
	dup2(pipex.fd_outfile, STDOUT_FILENO);
	execute(argv[argc - 2], pipex);
	return (0);
}

// this calls the function that is responsible for executing and parsing
void	ft_pipex(t_pipex pipex, int cmd_count)
{
	int		pipe_ret;
	int		end[2];

	pipe_ret = pipe(end);
	if (pipe_ret == -1)
		error("error while creating pipe");
	pipex.pid = fork();
	if (pipex.pid == -1)
		error("error while forking");
	if (pipex.pid == 0)
	{
		close(end[0]);
		dup2(end[1], STDOUT_FILENO);
		execute(pipex.argv[cmd_count], pipex);
	}
	else
	{
		close(end[1]);
		dup2(end[0], STDIN_FILENO);
		waitpid(pipex.pid, NULL, WNOHANG);
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
