/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmidt <kevin@imkx.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:27:19 by kschmidt          #+#    #+#             */
/*   Updated: 2023/03/10 19:05:42 by kschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parsing.h"

static char	**parse_all_args(char *arg_start, int i, int *j, t_shell *shell)
{
	char	**args;
	char	*arg;

	if (arg_start[*j])
	{
		arg = parse_next_arg(arg_start, j, shell);
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
	while (*cmd_start && (*cmd_start == ' ' || *cmd_start == '\t'
			|| *cmd_start == '<' || *cmd_start == '>' || *cmd_start == '|'))
		cmd_start++;
	return (cmd_start);
}

char	*parse_next_command(char *line, t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	j = i;
	cmd->name = parse_next_arg(line, &i, shell);
	cmd->args = parse_all_args(line, 0, &j, shell);
	cmd->argc = ft_arraylen(cmd->args);
	return (get_next_cmd_start(&cmd->next_type, line + j));
}
