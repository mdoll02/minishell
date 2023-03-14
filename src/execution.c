/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:08:07 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/14 08:11:26 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../includes/execution.h"
#include "libft.h"
#include "parsing.h"
#include "environment.h"

static int	check_builtin(t_shell *shell, t_cmd *cmd, int *status)
{
	int	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strncmp(g_builtins[i].name, cmd->name, 1000) == 0)
		{
			cmd->args++;
			cmd->argc--;
			*status = g_builtins[i].func(shell, cmd);
			cmd->args--;
			cmd->argc++;
			return (1);
		}
		i++;
	}
	return (0);
}

int	execute_command_child(t_cmd *cmd, t_env *env)
{
	char	**envp;
	int		result;
	pid_t	pid;

	envp = export_env(env);
	pid = fork();
	if (pid == 0)
		execve(cmd->name, cmd->args, envp);
	else
		waitpid(pid, &result, 0);
	WEXITSTATUS(result);
	ft_free_split(envp);
	return (result);
}

static int	execute_internal(t_shell *shell, t_cmd *cmd, int *status)
{
	char	*exec_path;

	if (check_builtin(shell, cmd, status))
		return (0);
	exec_path = get_exec_path(cmd->name, shell->env);
	if (exec_path)
	{
		free(cmd->name);
		cmd->name = exec_path;
		*status = execute_command_child(cmd, shell->env);
		return (0);
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd->name, 2);
	*status = 1;
	return (1);
}

int	execute(t_shell *shell, char *line, int *status)
{
	t_cmd	*cmd;
	int		result;
	int		i;

	if (!line || !*line)
		return (0);
	cmd = get_commands(shell, line);
	if (!cmd)
	{
		*status = 1;
		return (1);
	}
	i = 0;
	while (cmd[i].name)
		result = execute_internal(shell, &cmd[i++], status);
	free_commands(cmd);
	return (result);
}
