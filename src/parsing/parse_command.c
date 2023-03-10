/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:27:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 11:32:25 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parsing.h"

static char	**parse_all_args(char *arg_start, int i, int j, t_shell *shell)
{
	char	**args;
	char	*arg;

	if (!arg_start[j])
	{
		args = ft_calloc(i + 1, sizeof(char *));
		if (!args)
			return (0);
		args[i] = 0;
		return (args);
	}
	arg = parse_next_arg(arg_start, &j, shell);
	if (!arg)
		return (0);
	args = parse_all_args(arg_start, i + 1, j, shell);
	if (!args)
	{
		free(arg);
		return (0);
	}
	args[i] = arg;
	return (args);
}

int	parse_next_command(char *line, t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	cmd->name = parse_next_arg(line, &i, shell);
	if (!cmd->name)
		return (1);
	cmd->args = parse_all_args(line + i, 0, 0, shell);
	if (!cmd->args)
	{
		free(cmd->name);
		cmd->name = 0;
		return (1);
	}
	cmd->argc = ft_arraylen(cmd->args);
	return (0);
}
