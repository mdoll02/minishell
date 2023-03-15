/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:09:32 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/15 12:09:32 by mdoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <unistd.h>
#include "execution.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "pipeline.h"

int	redirect_input(t_cmd **cmd)
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

int	redirect_output(t_cmd *cmd)
{
	int	out_fd;

	if (cmd->next_type == CT_REDIRECT_OUT)
	{
		cmd++;
		out_fd = open(cmd->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else
	{
		cmd++;
		out_fd = open(cmd->name, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	if (out_fd == -1)
		return (out_fd);
	return (out_fd);
}
