/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:27:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/02/17 07:50:41 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parsing.h"

static char	**parse_args_rec(char *arg_start, int i, int j)
{
	char	**args;
	char	*arg;

	if (!arg_start[j])
	{
		args = ft_calloc(i, sizeof(char *));
		if (!args)
			return (0);
		args[i] = 0;
		return (args);
	}
	arg = parse_next_arg(arg_start, &j);
	if (!arg)
		return (0);
	args = parse_args_rec(arg_start, i + 1, j);
	if (!args)
	{
		free(arg);
		return (0);
	}
	args[i] = arg;
	return (args);
}

int	parse_command(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	cmd->name = parse_next_arg(line, &i);
	if (!cmd->name)
		return (1);
	cmd->args = parse_args_rec(line + i, 0, 0);
	if (!cmd->args)
	{
		free(cmd->name);
		cmd->name = 0;
		return (1);
	}
	cmd->argc = ft_arraylen(cmd->args);
	return (0);
}
