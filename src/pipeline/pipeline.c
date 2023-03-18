/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:35:14 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/15 11:38:50 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>
#include "execution.h"
#include "pipeline.h"


static void	restore_std_fds(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

static int	handle_final_case(t_shell *shell, t_cmd *cmd,
								int *status, t_fd_pipeline *pl)
{
	if (cmd->next_type == CT_REDIRECT_OUT || \
			cmd->next_type == CT_REDIRECT_OUTAPP)
		pl->output_fd = redirect_output(cmd);
	if (pl->output_fd == -1)
		return (pl->output_fd);
	dup2(pl->output_fd, STDOUT_FILENO);
	dup2(pl->input_fd, STDIN_FILENO);
	close(pl->input_fd);
	close(pl->output_fd);
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
		*status = handle_final_case(shell, *cmd, status, pl);
		return (0);
	}
	if ((*cmd)->next_type == CT_REDIRECT_HEREDOC)
	{
		(*cmd)++;
		(*cmd)++;
	}
	else
		(*cmd)++;
	return (-1);
}

int	exec_pipeline(t_shell *shell, t_cmd *cmd, int len, int *status)
{
	int				orig_stdin;
	int				orig_stdout;
	t_fd_pipeline	pl;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (check_for_heredoc(cmd, len) == true)
	{
		while (cmd->next_type != CT_REDIRECT_HEREDOC)
		{
			cmd++;
			len--;
		}
		cmd++;
		pl.input_fd = here_doc(cmd->name, cmd);
		cmd--;
		if (cmd->name == NULL)
		{
			cmd++;
			cmd++;
			len -= 2;
		}
		else
			len--;
	}
	else if (cmd->next_type == CT_REDIRECT_IN)
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
	pl.output_fd = orig_stdout;
	while (len--)
	{
		if (exec_pipeline_command(shell, &cmd, status,
				&pl) != -1)
			break ;
	}
	restore_std_fds(orig_stdin, orig_stdout);
	return (*status);
}
