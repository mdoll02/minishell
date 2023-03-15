/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoll <mdoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:09:32 by mdoll             #+#    #+#             */
/*   Updated: 2023/03/15 20:15:58 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
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
	int	open_flags;

	if (cmd->next_type == CT_REDIRECT_OUT)
		open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	else
		open_flags = O_WRONLY | O_CREAT | O_APPEND;
	cmd++;
	return (open(cmd->name, open_flags, 0644));
}
