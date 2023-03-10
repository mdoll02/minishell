/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:27:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 12:59:38 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parsing.h"

static char	**parse_all_args(char *arg_start, int i, int j, t_shell *shell)
{
	char	**args;
	char	*arg;

	if (arg_start[j])
	{
		arg = parse_next_arg(arg_start, &j, shell);
		if (arg)
		{
			args = parse_all_args(arg_start, i + 1, j, shell);
			if (!args)
			{
				free(arg);
				return (0);
			}
			args[i] = arg;
			return (args);
		}
	}
	args = ft_calloc(i + 1, sizeof(char *));
	if (!args)
		return (0);
	args[i] = 0;
	return (args);
}

static char	*get_next_cmd_start(int *next_type, char *line)
{
	char	*cmd_start;
	int		single_quotes;
	int		double_quotes;

	cmd_start = line;
	single_quotes = 0;
	double_quotes = 0;
	while (*cmd_start)
	{
		if (!single_quotes && !double_quotes)
		{
			if (is_cmd_end(next_type, cmd_start))
				break ;
		}
		if (*cmd_start == '\'' && !double_quotes)
			single_quotes++;
		if (*cmd_start == '"' && !single_quotes)
			double_quotes++;
		cmd_start++;
	}
	return (cmd_start);
}

char	*parse_next_command(char *line, t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	cmd->name = parse_next_arg(line, &i, shell);
	if (!cmd->name)
		return (0);
	cmd->args = parse_all_args(line + i, 0, 0, shell);
	if (!cmd->args)
	{
		free(cmd->name);
		cmd->name = 0;
		return (0);
	}
	cmd->argc = ft_arraylen(cmd->args);
	return (get_next_cmd_start(&cmd->next_type, line + i));
}
